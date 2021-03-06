#include <unistd.h>
#include <errno.h>

#include "liblops.h"

ssize_t readn(int fd, void* buf, size_t count)
{
    ssize_t i = 0;
    while(i < count)
    {
        ssize_t read_ = read(fd, buf + i, count - i);
        if(read_ == 0)
            break;
        if(read_ == -1)
        {
            if(errno == EAGAIN || errno == EINTR) continue;
            return -1;
        }
        i += read_;
    }
    return i;
}

ssize_t writen(int fd, const void* buf, size_t count)
{
    ssize_t i = 0;
    while(i < count)
    {
        ssize_t written = write(fd, buf + i, count - i);
        if(written == -1)
        {
            if(errno == EAGAIN || errno == EINTR) continue;
            return -1;
        }
        i += written;
    }
    return i;
}

ssize_t lread(int fd, void* buf, size_t count)
    __attribute__((deprecated, alias("readn")));
ssize_t lwrite(int fd, const void* buf, size_t count)
    __attribute__((deprecated, alias("writen")));
