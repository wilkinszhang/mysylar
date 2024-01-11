#ifndef MYSYLAR_LOG_H
#define MYSYLAR_LOG_H
#include<string>
#include<stdint.h>
#include<memory>
#include<list>
#include<sstream>
#include<fstream>
#include<vector>
#include<map>
#include"singleton.h"
#include"util.h"
#include"thread.h"
#define SYLAR_LOG_LEVEL(logger,level)\
    if(logger->getLevel()<=level)\
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger,level,__FILE__,__LINE__,0,sylar::GetThreadId(),\
        sylar::GetFiberId(),time(0), sylar::Thread::GetName()))).getSS()

#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::DEBUG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::INFO)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::FATAL)

#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()

#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)

#define SYLAR_LOG_FMT_LEVEL(logger,level,fmt,...)\
    if(logger->getLevel()<=level)\
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger,level,\
                            __FILE__,__LINE__,0,sylar::GetThreadId(),\
                            sylar::GetFiberId(),time(0), sylar::Thread::GetName()))).getEvent()->format(fmt,__VA_ARGS__)
//__VA_ARGS__ 是一个特殊的预处理器标识符，用于表示宏中的可变参数。
#define SYLAR_LOG_FMT_DEBUG(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::DEBUG,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_INFO(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::INFO,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_WARN(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::WARN,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_ERROR(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::ERROR,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_FATAL(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::FATAL,fmt,__VA_ARGS__)

namespace sylar{
    class Logger;
    class LoggerManager;

    //日志级别
    class LogLevel
    {
    public:
        enum Level{
                UNKNOW=0,
                DEBUG=1,
                INFO=2,
                WARN=3,
                ERROR=4,
                FATAL=5
        };
        static const char* ToString(LogLevel::Level level);
        static LogLevel::Level FromString(const std::string& str);
    };

    //日志事件
    class LogEvent
    {
    private:
        std::shared_ptr<Logger> m_logger;
        LogLevel::Level m_level;
        const char * m_file = nullptr;
        int32_t m_line=0;
        uint32_t m_elapse=0;
        uint32_t m_threadId=0;
        uint32_t m_fiberId=0;
        uint64_t m_time=0;
        std::stringstream m_ss;
        std::string m_threadName;
    public:
        LogEvent(std::shared_ptr<Logger> logger,LogLevel::Level level,const char* file,int32_t line,
                uint32_t elapse,uint32_t thread_id,uint32_t fiber_id,uint64_t time,const std::string& thread_name);
        typedef std::shared_ptr<LogEvent> ptr;
        const char * getFile() const {return m_file;}
        int32_t getLine() const {return m_line;}
        uint32_t getElapse() const {return m_elapse;}
        uint32_t getThreadId() const {return m_threadId;}
        uint32_t getFiberId() const {return m_fiberId;}
        uint64_t getTime() const {return m_time;}
        std::string getContent() const {return m_ss.str();}
        std::stringstream& getSS(){return m_ss;}
        std::string getThreadName() const {return m_threadName;}
        std::shared_ptr<Logger> getLogger() const {return m_logger;}
        LogLevel::Level getLevel() const {return m_level;}
        void setFile(const char * file){m_file=file;}
        void setLine(int32_t line){m_line=line;}
        void setElapse(uint32_t elapse){m_elapse=elapse;}
        void setThreadId(uint32_t threadid){m_threadId=threadid;}
        void setFiberId(uint32_t fiberid){m_fiberId=fiberid;}
        void setTime(uint64_t time){m_time=time;}
        // void setContent(std::string content){m_content=content;}
        void setThreadName(std::string threadName){m_threadName=threadName;}
        void setLogger(std::shared_ptr<Logger> logger){m_logger=logger;}
        void setLevel(LogLevel::Level level){m_level=level;}

        void format(const char* fmt, ...);
        void format(const char* fmt, va_list al);
    };
    
    class LogEventWrap
    {
    private:
        LogEvent::ptr m_event;
    public:
        LogEventWrap(LogEvent::ptr e);
        ~LogEventWrap();
        std::stringstream& getSS();
        LogEvent::ptr getEvent(){return m_event;}
    };
    
    //日志格式器
    class LogFormatter
    {
    public:
        LogFormatter(const std::string & pattern)
        :m_pattern(pattern)
        {
            init();
        }
        typedef std::shared_ptr<LogFormatter> ptr;
        //%t %thread_id %m %n
        std::string format(std::shared_ptr<Logger>ptr,LogLevel::Level level,LogEvent::ptr event);
        void init();
        class FormatItem
        {
        public:
            virtual void format(std::ostream& os,std::shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event)=0;
            typedef std::shared_ptr<FormatItem> ptr;
        private:
            std::string m_pattern;
            std::vector<FormatItem::ptr> m_items;
        };
        bool isError(){return m_error;}
        const std::string getPattern() const {return m_pattern;}
    private:
        std::string m_pattern;
        std::vector<FormatItem::ptr> m_items;
        bool m_error=false;
    };

    //日志输出地
    class LogAppender
    {
    friend class Logger;
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        typedef Spinlock MutexType;
        virtual void log(std::shared_ptr<Logger> logger,LogLevel::Level level, LogEvent::ptr event)=0;
        void setFormatter(LogFormatter::ptr val);
        LogLevel::Level getLevel() const {return m_level;}
        void setLevel(LogLevel::Level level){m_level=level;}
        LogFormatter::ptr getFormatter();
        virtual std::string toYamlString()=0;
    protected:
        LogLevel::Level m_level = LogLevel::DEBUG;
        LogFormatter::ptr m_formatter;
        bool m_hasFormatter = false;
        MutexType m_mutex;
    };
        
    //日志器
    class Logger : public std::enable_shared_from_this<Logger>
    {
        friend class LoggerManager;

    public:
        Logger(const std::string& name = "root") : 
                    m_name(name),m_level(LogLevel::DEBUG) {
            m_formatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));//使用reset函数而不是直接赋值，
            //是因为reset可以在赋值的同时删除原来的对象，避免内存泄漏
        }
        typedef std::shared_ptr<Logger> ptr;
        typedef Spinlock MutexType;
        
        void log(LogLevel::Level level, LogEvent::ptr event);
        void debug(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void warn(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);
        void addAppender(LogAppender::ptr appender);
        void delAppender(LogAppender::ptr appender);
        LogLevel::Level getLevel()const{return m_level;}
        void setLevel(LogLevel::Level level){m_level=level;}
        void setFormatter(LogFormatter::ptr lf);
        void setFormatter(const std::string& str);
        std::string getName(){return m_name;}
        LogFormatter::ptr getFormatter();
        void clearAppenders();
        std::string toYamlString();
    private:
        std::string m_name;
        LogLevel::Level m_level;
        std::list<LogAppender::ptr> m_appenders;
        LogFormatter::ptr m_formatter;
        Logger::ptr m_root;
        MutexType m_mutex;
    };
    
    //定义输出到控制台的Appender
    class StdoutLogAppender : public LogAppender
    {
    friend class Logger;
    public:
        typedef std::shared_ptr<StdoutLogAppender> ptr;
        virtual void log(std::shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event) override;
        std::string toYamlString() override;
    };
    
    //定义输出到文件的Appender
    class FileLogAppender :public LogAppender
    {
    friend class Logger;
    private:
        std::string m_filename;
        std::ofstream m_filestream;
        uint64_t m_lastTime=0;
    public:
        FileLogAppender(const std::string & filename)
        :m_filename(filename)
        {
            reopen();
        }
        typedef std::shared_ptr<FileLogAppender> ptr;
        void log(std::shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event) override;
        bool reopen();
        std::string toYamlString() override;
    };

    class LoggerManager
    {
    public:
        LoggerManager();
        Logger::ptr getLogger(const std::string &name);
        Logger::ptr getRoot() const {return m_root;}
        void init();
        std::string toYamlString();
        typedef Spinlock MutexType;
    private:
        std::map<std::string,Logger::ptr> m_loggers;
        Logger::ptr m_root;
        MutexType m_mutex;
    };
    
    typedef sylar::Singleton<LoggerManager> LoggerMgr;
}
#endif