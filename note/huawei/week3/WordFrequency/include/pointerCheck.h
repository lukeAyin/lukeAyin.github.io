#ifndef POINTER_CHECK_H__
#define POINTER_CHECK_H__

#define CHECK_NULL_RETURN_NULL(p) \
    {                             \
        if (NULL == (p)) {        \
            return NULL;          \
        }                         \
    }
#define CHECK_NULL_RETURN_ZERO(p) \
    {                             \
        if (NULL == (p)) {        \
            return 0;             \
        }                         \
    }
#define CHECK_NULL_RETURN_VOID(p) \
    {                             \
        if (NULL == (p)) {        \
            return;               \
        }                         \
    }

#endif /* POINTER_CHECK_H__ */