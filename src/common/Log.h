//*********************************//
//File:         Log.h
//Auther:       xst
//History:
//  xst         2016/9/17       create
//*********************************//


#ifndef SA_COMMON_LOG__H
#define SA_COMMON_LOG__H

#include <ostream>

enum EMLogTag
{
    INFO,
    WARNING,
    ERROR,
};

#define SaLog(tag, msg)


struct None { };

template <typename First, typename Second>
struct Pair {
    First first;
    Second second;
};

template <typename List>
struct LogData {
    List list;
};

template <typename Begin, typename Value>
LogData<Pair<Begin, const Value &>>
operator<<(LogData<Begin> begin, const Value &value)
{
    return{ { begin.list, value } };
}

template <typename Begin, size_t n>
LogData<Pair<Begin, const char *>>
operator<<(LogData<Begin> begin, const char(&value)[n])
{
    return{ { begin.list, value } };
}

inline void printList(std::ostream &os, None)
{
}


template <typename Begin, typename Last>
void printList(std::ostream &os, const Pair<Begin, Last> &data)
{
    printList(os, data.first);
    os << data.second;
}

template <typename List>
void SaLogImpl(EMLogTag tag, const char *file, int line, const LogData<List> &data)
{
    switch (tag)
    {
    case INFO:
    {
        std::cout << "[I]";
        break;
    }
    case WARNING:
    {
        std::cout << "[W]";
        break;
    }
    case ERROR:
    {
        std::cout << "[E]";
        break;
    }
    default:
    {
        std::cout << "[U]";
        break;
    }
    }

    std::cout << file << " (" << line << "): ";
    printList(std::cout, data.list);
    std::cout << std::endl;
}

#define SaLog(tag, data) (SaLogImpl(tag, __FILE__, __LINE__, LogData<None>() << data))
#endif //SA_COMMON_LOG__H