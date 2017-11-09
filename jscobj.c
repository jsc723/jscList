#include "jscobj.h"

void *_obj_arg_;
void *__method__(void *obj){_obj_arg_ = obj;return obj;}
