#ifndef JSCOBJ_H
#define JSCOBJ_H

#define this m(self)
#define m(pInst) ((pInst)->_method_(pInst))

#define Def_Method(T) T * T##$Method(T *ps){return (T *)__method__(ps);}
#define Dec_Method(T) struct T * (* _method_)(struct T * ps);
#define Ist_Method(pInst,T) pInst->_method_ = T##$Method;
#define getSelf(T) T * self = (T *)_obj_arg_;


extern void *_obj_arg_;
extern void *__method__(void *obj);


#endif
