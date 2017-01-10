import sys

import omi
from omi import *

import random

import ctypes


COPY_CTOR = False
ASSIGN_OP = False


class Foo (object):
    def __init__ (self,value):
        self.value = value

    def __str__ (self):
        return self.value.__str__ ()



def bool_test ():
    be = BookEnd ('bool_test')

    rval = True

    # init (empty)
    v0 = MI_Boolean ()
    if v0.getType () != MI_BOOLEAN:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Boolean (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to literal value
    v2 = MI_Boolean (True)
    if v2.value != True:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Boolean (None)
    t3 = MI_Boolean ()
    if COPY_CTOR:
        v3 = MI_Boolean (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Boolean (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Boolean (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Boolean
    t4 = MI_Boolean (False)
    if COPY_CTOR:
        v4 = MI_Boolean (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Boolean init failed')
            rval = False
    else:
        try:
            v4 = MI_Boolean (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Uint8 ()
    try:
        v5 = MI_Boolean (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Uint8 (6)
    try:
        v6 = MI_Boolean (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Boolean ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # assign None to None
    v8 = MI_Boolean ()
    v8.value = None
    if v8.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a literal value to None
    v9 = MI_Boolean ()
    v9.value = True
    if v9.value != True:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Boolean (None) to None
    v10 = MI_Boolean ()
    t10 = MI_Boolean ()
    if ASSIGN_OP:
        v10.value = t10
        if v10.value != t10.value:
            BookEndPrint ('----- MI_Boolean (None) assignment to None failed')
            rval = false
    else:
        try:
            v10.value = t10
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Boolean to None
    v11 = MI_Boolean ()
    t11 = MI_Boolean (False)
    if ASSIGN_OP:
        v11.value = t11
        if v11.value != t11.value:
            BookEndPrint ('----- MI_Boolean assignment to None failed')
            rval = false
    else:
        try:
            v11.value = t11
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v12 = MI_Boolean ()
    t12 = MI_Uint8 ()
    try:
        v12.value = t12
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v13 = MI_Boolean ()
    t13 = MI_Uint8 (13)
    try:
        v13.value = t13
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v14 = MI_Boolean ()
    try:
        v14.value = 'fourteen'
    except:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign None
    v15 = MI_Boolean (True)
    v15.value = None
    if v15.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    v16 = MI_Boolean (False)
    v16.value = True
    if v16.value != True:
        BookEndPrint ('----- literal value assignment failed')
        rval = false

    # assign MI_Boolean (None)
    v17 = MI_Boolean (True)
    t17 = MI_Boolean ()
    if ASSIGN_OP:
        v17.value = t17
        if v17.value != t17.value:
            BookEndPrint ('----- MI_Boolean (None) assignment failed')
            rval = false
    else:
        try:
            v17.value = t17
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Boolean
    v18 = MI_Boolean (False)
    t18 = MI_Boolean (True)
    if ASSIGN_OP:
        v18.value = t18
        if v18.value != t18.value:
            BookEndPrint ('----- MI_Boolean assignment failed')
            rval = false
    else:
        try:
            v18.value = t18
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v19 = MI_Boolean (False)
    t19 = MI_Uint8 ()
    try:
        v19.value = t19
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign a different MI type **error**
    v20 = MI_Boolean (True)
    t20 = MI_Uint8 (20)
    try:
        v20.value = t20
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v21 = MI_Boolean (False)
    try:
        v21.value = 'twenty-one'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Boolean)')

    return rval


def uint8_test ():
    be = BookEnd ('uint8_test')
    
    rval = True

    # init (empty)
    v0 = MI_Uint8 ()
    if v0.getType () != MI_UINT8:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Uint8 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (0, 0xFF)
    v2 = MI_Uint8 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Uint8 (None)
    t3 = MI_Uint8 ()
    if COPY_CTOR:
        v3 = MI_Uint8 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Uint8 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Uint8 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Uint8
    t4 = MI_Uint8 (random.randint (0, 0xFF))
    if COPY_CTOR:
        v4 = MI_Uint8 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Uint8 init failed')
            rval = False
    else:
        try:
            v4 = MI_Uint8 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Uint8 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Uint8 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Uint8 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Uint8 (-1)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Uint8 (0x100)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Uint8 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Uint8 ()
    r11 = random.randint (0, 0xFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Uint8 (None) to None
    v12 = MI_Uint8 ()
    t12 = MI_Uint8 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Uint8 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint8 to None
    v13 = MI_Uint8 ()
    t13 = MI_Uint8 (random.randint (0, 0xFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Uint8 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Uint8 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Uint8 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Uint8 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Uint8 ()
    try:
        v17.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Uint8 ()
    try:
        v18.value = 0x100
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Uint8 (random.randint (0, 0xFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (0, 0xFF)
    r20b = random.randint (0, 0xFF)
    while r20a == r20b:
        r20b = random.randint (0, 0xFF)
    v20 = MI_Uint8 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Uint8 (None)
    v21 = MI_Uint8 (random.randint (0, 0xFF))
    t21 = MI_Uint8 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Uint8 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint8
    r22a = random.randint (0, 0xFF)
    r22b = random.randint (0, 0xFF)
    while r22a == r22b:
        r22b = random.randint (0, 0xFF)
    v22 = MI_Uint8 (r22a)
    t22 = MI_Uint8 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Uint8 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Uint8 (random.randint (0, 0xFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Uint8 (random.randint (0, 0xFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Uint8 (random.randint (0, 0xFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Uint8 (random.randint (0, 0xFF))
    try:
        v26.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Uint8 (random.randint (0, 0xFF))
    try:
        v27.value = 0x100
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint8)')

    return rval


def sint8_test ():
    be = BookEnd ('sint8_test')
    
    rval = True

    # init (empty)
    v0 = MI_Sint8 ()
    if v0.getType () != MI_SINT8:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Sint8 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (-0x80, 0x7F)
    v2 = MI_Sint8 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Sint8 (None)
    t3 = MI_Sint8 ()
    if COPY_CTOR:
        v3 = MI_Sint8 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Sint8 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Sint8 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Sint8
    t4 = MI_Sint8 (random.randint (-0x80, 0x7F))
    if COPY_CTOR:
        v4 = MI_Sint8 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Sint8 init failed')
            rval = False
    else:
        try:
            v4 = MI_Sint8 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Sint8 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Sint8 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Sint8 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Sint8 (-0x81)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Sint8 (0x80)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Sint8 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Sint8 ()
    r11 = random.randint (-0x80, 0x7F)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Sint8 (None) to None
    v12 = MI_Sint8 ()
    t12 = MI_Sint8 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Sint8 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint8 to None
    v13 = MI_Sint8 ()
    t13 = MI_Sint8 (random.randint (-0x80, 0x7F))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Sint8 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Sint8 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Sint8 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Sint8 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Sint8 ()
    try:
        v17.value = -0x81
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Sint8 ()
    try:
        v18.value = 0x80
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Sint8 (random.randint (-0x80, 0x7F))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (-0x80, 0x7F)
    r20b = random.randint (-0x80, 0x7F)
    while r20a == r20b:
        r20b = random.randint (-0x80, 0x7F)
    v20 = MI_Sint8 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Sint8 (None)
    v21 = MI_Sint8 (random.randint (-0x80, 0x7F))
    t21 = MI_Sint8 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Sint8 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint8
    r22a = random.randint (-0x80, 0x7F)
    r22b = random.randint (-0x80, 0x7F)
    while r22a == r22b:
        r22b = random.randint (-0x80, 0x7F)
    v22 = MI_Sint8 (r22a)
    t22 = MI_Sint8 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Sint8 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Sint8 (random.randint (-0x80, 0x7F))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Sint8 (random.randint (-0x80, 0x7F))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Sint8 (random.randint (-0x80, 0x7F))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Sint8 (random.randint (-0x80, 0x7F))
    try:
        v26.value = -0x81
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Sint8 (random.randint (-0x80, 0x7F))
    try:
        v27.value = 0x80
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint8)')

    return rval


def uint16_test ():
    be = BookEnd ('uint16_test')
    
    rval = True

    # init (empty)
    v0 = MI_Uint16 ()
    if v0.getType () != MI_UINT16:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Uint16 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (0, 0xFFFF)
    v2 = MI_Uint16 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Uint16 (None)
    t3 = MI_Uint16 ()
    if COPY_CTOR:
        v3 = MI_Uint16 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Uint16 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Uint16 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Uint16
    t4 = MI_Uint16 (random.randint (0, 0xFFFF))
    if COPY_CTOR:
        v4 = MI_Uint16 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Uint16 init failed')
            rval = False
    else:
        try:
            v4 = MI_Uint16 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Uint16 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Uint16 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Uint16 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Uint16 (-1)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Uint16 (0x10000)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Uint16 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Uint16 ()
    r11 = random.randint (0, 0xFFFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Uint16 (None) to None
    v12 = MI_Uint16 ()
    t12 = MI_Uint16 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Uint16 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint16 to None
    v13 = MI_Uint16 ()
    t13 = MI_Uint16 (random.randint (0, 0xFFFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Uint16 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Uint16 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Uint16 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Uint16 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Uint16 ()
    try:
        v17.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Uint16 ()
    try:
        v18.value = 0x10000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Uint16 (random.randint (0, 0xFFFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (0, 0xFFFF)
    r20b = random.randint (0, 0xFFFF)
    while r20a == r20b:
        r20b = random.randint (0, 0xFFFF)
    v20 = MI_Uint16 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Uint16 (None)
    v21 = MI_Uint16 (random.randint (0, 0xFFFF))
    t21 = MI_Uint16 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Uint16 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint16
    r22a = random.randint (0, 0xFFFF)
    r22b = random.randint (0, 0xFFFF)
    while r22a == r22b:
        r22b = random.randint (0, 0xFFFF)
    v22 = MI_Uint16 (r22a)
    t22 = MI_Uint16 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Uint16 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Uint16 (random.randint (0, 0xFFFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Uint16 (random.randint (0, 0xFFFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Uint16 (random.randint (0, 0xFFFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Uint16 (random.randint (0, 0xFFFF))
    try:
        v26.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Uint16 (random.randint (0, 0xFFFF))
    try:
        v27.value = 0x10000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint16)')

    return rval


def sint16_test ():
    be = BookEnd ('sint16_test')
    
    rval = True

    # init (empty)
    v0 = MI_Sint16 ()
    if v0.getType () != MI_SINT16:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Sint16 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (-0x8000, 0x7FFF)
    v2 = MI_Sint16 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Sint16 (None)
    t3 = MI_Sint16 ()
    if COPY_CTOR:
        v3 = MI_Sint16 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Sint16 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Sint16 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Sint16
    t4 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    if COPY_CTOR:
        v4 = MI_Sint16 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Sint16 init failed')
            rval = False
    else:
        try:
            v4 = MI_Sint16 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Sint16 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Sint16 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Sint16 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Sint16 (-0x8001)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Sint16 (0x8000)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Sint16 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Sint16 ()
    r11 = random.randint (-0x8000, 0x7FFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Sint16 (None) to None
    v12 = MI_Sint16 ()
    t12 = MI_Sint16 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Sint16 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint16 to None
    v13 = MI_Sint16 ()
    t13 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Sint16 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Sint16 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Sint16 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Sint16 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Sint16 ()
    try:
        v17.value = -0x8001
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Sint16 ()
    try:
        v18.value = 0x8000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (-0x8000, 0x7FFF)
    r20b = random.randint (-0x8000, 0x7FFF)
    while r20a == r20b:
        r20b = random.randint (-0x8000, 0x7FFF)
    v20 = MI_Sint16 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Sint16 (None)
    v21 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    t21 = MI_Sint16 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Sint16 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint16
    r22a = random.randint (-0x8000, 0x7FFF)
    r22b = random.randint (-0x8000, 0x7FFF)
    while r22a == r22b:
        r22b = random.randint (-0x8000, 0x7FFF)
    v22 = MI_Sint16 (r22a)
    t22 = MI_Sint16 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Sint16 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    try:
        v26.value = -0x8001
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Sint16 (random.randint (-0x8000, 0x7FFF))
    try:
        v27.value = 0x8000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint16)')

    return rval


def uint32_test ():
    be = BookEnd ('uint32_test')
    
    rval = True

    # init (empty)
    v0 = MI_Uint32 ()
    if v0.getType () != MI_UINT32:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Uint32 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (0, 0xFFFFFFFF)
    v2 = MI_Uint32 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Uint32 (None)
    t3 = MI_Uint32 ()
    if COPY_CTOR:
        v3 = MI_Uint32 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Uint32 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Uint32 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Uint32
    t4 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    if COPY_CTOR:
        v4 = MI_Uint32 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Uint32 init failed')
            rval = False
    else:
        try:
            v4 = MI_Uint32 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Uint32 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Uint32 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Uint32 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Uint32 (-1)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Uint32 (0x100000000)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Uint32 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Uint32 ()
    r11 = random.randint (0, 0xFFFFFFFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Uint32 (None) to None
    v12 = MI_Uint32 ()
    t12 = MI_Uint32 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Uint32 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint32 to None
    v13 = MI_Uint32 ()
    t13 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Uint32 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Uint32 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Uint32 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Uint32 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Uint32 ()
    try:
        v17.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Uint32 ()
    try:
        v18.value = 0x100000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (0, 0xFFFFFFFF)
    r20b = random.randint (0, 0xFFFFFFFF)
    while r20a == r20b:
        r20b = random.randint (0, 0xFFFFFFFF)
    v20 = MI_Uint32 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Uint32 (None)
    v21 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    t21 = MI_Uint32 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Uint32 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint32
    r22a = random.randint (0, 0xFFFFFFFF)
    r22b = random.randint (0, 0xFFFFFFFF)
    while r22a == r22b:
        r22b = random.randint (0, 0xFFFFFFFF)
    v22 = MI_Uint32 (r22a)
    t22 = MI_Uint32 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Uint32 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    try:
        v26.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Uint32 (random.randint (0, 0xFFFFFFFF))
    try:
        v27.value = 0x100000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint32)')

    return rval


def sint32_test ():
    be = BookEnd ('sint32_test')
    
    rval = True

    # init (empty)
    v0 = MI_Sint32 ()
    if v0.getType () != MI_SINT32:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Sint32 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (-0x80000000, 0x7FFFFFFF)
    v2 = MI_Sint32 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Sint32 (None)
    t3 = MI_Sint32 ()
    if COPY_CTOR:
        v3 = MI_Sint32 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Sint32 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Sint32 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Sint32
    t4 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    if COPY_CTOR:
        v4 = MI_Sint32 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Sint32 init failed')
            rval = False
    else:
        try:
            v4 = MI_Sint32 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Sint32 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Sint32 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Sint32 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Sint32 (-0x80000001)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Sint32 (0x80000000)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Sint32 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Sint32 ()
    r11 = random.randint (-0x80000000, 0x7FFFFFFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Sint32 (None) to None
    v12 = MI_Sint32 ()
    t12 = MI_Sint32 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Sint32 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint32 to None
    v13 = MI_Sint32 ()
    t13 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Sint32 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Sint32 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Sint32 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Sint32 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Sint32 ()
    try:
        v17.value = -0x80000001
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Sint32 ()
    try:
        v18.value = 0x80000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (-0x80000000, 0x7FFFFFFF)
    r20b = random.randint (-0x80000000, 0x7FFFFFFF)
    while r20a == r20b:
        r20b = random.randint (-0x80000000, 0x7FFFFFFF)
    v20 = MI_Sint32 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Sint32 (None)
    v21 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    t21 = MI_Sint32 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Sint32 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint32
    r22a = random.randint (-0x80000000, 0x7FFFFFFF)
    r22b = random.randint (-0x80000000, 0x7FFFFFFF)
    while r22a == r22b:
        r22b = random.randint (-0x80000000, 0x7FFFFFFF)
    v22 = MI_Sint32 (r22a)
    t22 = MI_Sint32 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Sint32 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    try:
        v26.value = -0x80000001
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Sint32 (random.randint (-0x80000000, 0x7FFFFFFF))
    try:
        v27.value = 0x80000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint32)')

    return rval


def uint64_test ():
    be = BookEnd ('uint64_test')
    
    rval = True

    # init (empty)
    v0 = MI_Uint64 ()
    if v0.getType () != MI_UINT64:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Uint64 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    v2 = MI_Uint64 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Uint64 (None)
    t3 = MI_Uint64 ()
    if COPY_CTOR:
        v3 = MI_Uint64 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Uint64 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Uint64 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Uint64
    t4 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    if COPY_CTOR:
        v4 = MI_Uint64 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Uint64 init failed')
            rval = False
    else:
        try:
            v4 = MI_Uint64 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Uint64 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Uint64 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Uint64 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Uint64 (-1)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Uint64 (0x10000000000000000)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Uint64 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Uint64 ()
    r11 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Uint64 (None) to None
    v12 = MI_Uint64 ()
    t12 = MI_Uint64 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Uint64 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint64 to None
    v13 = MI_Uint64 ()
    t13 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Uint64 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Uint64 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Uint64 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Uint64 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Uint64 ()
    try:
        v17.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Uint64 ()
    try:
        v18.value = 0x10000000000000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    r20b = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while r20a == r20b:
        r20b = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    v20 = MI_Uint64 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Uint64 (None)
    v21 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    t21 = MI_Uint64 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Uint64 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Uint64
    r22a = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    r22b = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while r22a == r22b:
        r22b = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    v22 = MI_Uint64 (r22a)
    t22 = MI_Uint64 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Uint64 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    try:
        v26.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Uint64 (random.randint (0, 0xFFFFFFFFFFFFFFFF))
    try:
        v27.value = 0x10000000000000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint64)')

    return rval


def sint64_test ():
    be = BookEnd ('sint64_test')
    
    rval = True

    # init (empty)
    v0 = MI_Sint64 ()
    if v0.getType () != MI_SINT64:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Sint64 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    v2 = MI_Sint64 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Sint64 (None)
    t3 = MI_Sint64 ()
    if COPY_CTOR:
        v3 = MI_Sint64 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Sint64 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Sint64 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Sint64
    t4 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    if COPY_CTOR:
        v4 = MI_Sint64 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Sint64 init failed')
            rval = False
    else:
        try:
            v4 = MI_Sint64 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Sint64 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Sint64 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Sint64 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Sint64 (-0x8000000000000001)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Sint64 (0x8000000000000000)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Sint64 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Sint64 ()
    r11 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Sint64 (None) to None
    v12 = MI_Sint64 ()
    t12 = MI_Sint64 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Sint64 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint64 to None
    v13 = MI_Sint64 ()
    t13 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Sint64 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Sint64 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Sint64 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Sint64 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Sint64 ()
    try:
        v17.value = -0x8000000000000001
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Sint64 ()
    try:
        v18.value = 0x8000000000000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    r20b = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while r20a == r20b:
        r20b = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    v20 = MI_Sint64 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Sint64 (None)
    v21 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    t21 = MI_Sint64 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Sint64 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Sint64
    r22a = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    r22b = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while r22a == r22b:
        r22b = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    v22 = MI_Sint64 (r22a)
    t22 = MI_Sint64 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Sint64 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    try:
        v26.value = -0x8000000000000001
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Sint64 (random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF))
    try:
        v27.value = 0x8000000000000000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint64)')

    return rval


def float_eq (left, right):
    if (left > 0 and right > 0):
        if left > right:
            return (left - right) < sys.float_info.epsilon
        else:
            return (right - left) < sys.float_info.epsilon
    elif (left < 0 and right < 0):
        if left < right:
            return (left - right) < sys.float_info.epsilon
        else:
            return (right - left) < sys.float_info.epsilon
    return False


def real32_test ():
    be = BookEnd ('real32_test')

    rval = True

    # init (empty)
    v0 = MI_Real32 ()
    if v0.getType () != MI_REAL32:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Real32 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False

    # init to value
    r2 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v2 = MI_Real32 (r2.value)
    if not float_eq (v2.value, r2.value):
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Real32 (None)
    t3 = MI_Real32 ()
    if COPY_CTOR:
        v3 = MI_Real32 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Real32 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Real32 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Real32
    r4 = ctypes.c_float (random.uniform (-1e37, 1e37))
    t4 = MI_Real32 (r4.value)
    if COPY_CTOR:
        v4 = MI_Real32 (t4)
        if not float_eq (t4.value, v4.value):
            BookEndPrint ('----- MI_Real32 init failed')
            rval = False
    else:
        try:
            v4 = MI_Real32 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Real32 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Real32 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False

    # init to invalid literal value **error**
    try:
        v7 = MI_Real32 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Real32 (-1e39)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Real32 (1e39)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Real32 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a value to None
    r11 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v11 = MI_Real32 ()
    v11.value = r11.value
    if not float_eq (v11.value, r11.value):
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Real32 (None) to None
    v12 = MI_Real32 ()
    t12 = MI_Real32 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Real32 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Real32 to None
    r13 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v13 = MI_Real32 ()
    t13 = MI_Real32 (r13.value)
    if ASSIGN_OP:
        v13.value = t13
        if not float_eq (v13.value, t13.value):
            BookEndPrint ('----- MI_Real32 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign a different MI type (None) to None **error**
    v14 = MI_Real32 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type to None **error**
    v15 = MI_Real32 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Real32 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Real32 ()
    try:
        v17.value = -1e39
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Real32 ()
    try:
        v18.value = 1e39
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    ## assign None
    r19 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v19 = MI_Real32 (r19.value)
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = ctypes.c_float (random.uniform (-1e37, 1e37))
    r20b = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (r20a.value, r20b.value):
        r20b = ctypes.c_float (random.uniform (-1e37, 1e37))
    v20 = MI_Real32 (r20a.value)
    v20.value = r20b.value
    if not float_eq (v20.value, r20b.value):
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Real32 (None)
    r21 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v21 = MI_Real32 (r21.value)
    t21 = MI_Real32 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Real32 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Real32
    r22a = ctypes.c_float (random.uniform (-1e37, 1e37))
    r22b = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (r22a.value, r22b.value):
        r22b = ctypes.c_float (random.uniform (-1e37, 1e37))
    v22 = MI_Real32 (r22a.value)
    t22 = MI_Real32 (r22b.value)
    if ASSIGN_OP:
        v22.value = t22
        if not float_eq (v22.value, t22.value):
            BookEndPrint ('----- MI_Real32 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign a different MI type (None) **error**
    r23 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v23 = MI_Real32 (r23.value)
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    r24 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v24 = MI_Real32 (r24.value)
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    r25 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v25 = MI_Real32 (r25.value)
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    r26 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v26 = MI_Real32 (r26.value)
    try:
        v26.value = -1e39
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    r27 = ctypes.c_float (random.uniform (-1e37, 1e37))
    v27 = MI_Real32 (r27.value)
    try:
        v27.value = 1e39
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Real32)')

    return rval


def real64_test ():
    be = BookEnd ('real64_test')

    rval = True

    # init (empty)
    v0 = MI_Real64 ()
    if v0.getType () != MI_REAL64:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Real64 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False

    # init to value
    r2 = random.uniform (-1e307, 1e307)
    v2 = MI_Real64 (r2)
    if not float_eq (v2.value, r2):
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Real64 (None)
    t3 = MI_Real64 ()
    if COPY_CTOR:
        v3 = MI_Real64 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Real64 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Real64 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Real64
    r4 = random.uniform (-1e307, 1e307)
    t4 = MI_Real64 (r4)
    if COPY_CTOR:
        v4 = MI_Real64 (t4)
        if not float_eq (t4.value, v4.value):
            BookEndPrint ('----- MI_Real64 init failed')
            rval = False
    else:
        try:
            v4 = MI_Real64 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Real64 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Real64 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False

    # init to invalid literal value **error**
    try:
        v7 = MI_Real64 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Real64 (-1e309)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Real64 (1e309)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Real64 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a value to None
    r11 = random.uniform (-1e307, 1e307)
    v11 = MI_Real64 ()
    v11.value = r11
    if not float_eq (v11.value, r11):
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Real64 (None) to None
    v12 = MI_Real64 ()
    t12 = MI_Real64 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Real64 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Real64 to None
    r13 = random.uniform (-1e307, 1e307)
    v13 = MI_Real64 ()
    t13 = MI_Real64 (r13)
    if ASSIGN_OP:
        v13.value = t13
        if not float_eq (v13.value, t13.value):
            BookEndPrint ('----- MI_Real64 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign a different MI type (None) to None **error**
    v14 = MI_Real64 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type to None **error**
    v15 = MI_Real64 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Real64 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Real64 ()
    try:
        v17.value = -1e309
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Real64 ()
    try:
        v18.value = 1e309
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    r19 = random.uniform (-1e307, 1e307)
    v19 = MI_Real64 (r19)
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.uniform (-1e307, 1e307)
    r20b = random.uniform (-1e307, 1e307)
    while float_eq (r20a, r20b):
        r20b = random.uniform (-1e307, 1e307)
    v20 = MI_Real64 (r20a)
    v20.value = r20b
    if not float_eq (v20.value, r20b):
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Real64 (None)
    r21 = random.uniform (-1e307, 1e307)
    v21 = MI_Real64 (r21)
    t21 = MI_Real64 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Real64 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Real64
    r22a = random.uniform (-1e307, 1e307)
    r22b = random.uniform (-1e307, 1e307)
    while float_eq (r22a, r22b):
        r22b = random.uniform (-1e307, 1e307)
    v22 = MI_Real64 (r22a)
    t22 = MI_Real64 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if not float_eq (v22.value, t22.value):
            BookEndPrint ('----- MI_Real64 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign a different MI type (None) **error**
    r23 = random.uniform (-1e307, 1e307)
    v23 = MI_Real64 (r23)
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    r24 = random.uniform (-1e307, 1e307)
    v24 = MI_Real64 (r24)
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    r25 = random.uniform (-1e307, 1e307)
    v25 = MI_Real64 (r25)
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    r26 = random.uniform (-1e307, 1e307)
    v26 = MI_Real64 (r26)
    try:
        v26.value = -1e309
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    r27 = random.uniform (-1e307, 1e307)
    v27 = MI_Real64 (r27)
    try:
        v27.value = 1e309
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Real64)')

    return rval


def char16_test ():
    be = BookEnd ('char16_test')
    
    rval = True

    # init (empty)
    v0 = MI_Char16 ()
    if v0.getType () != MI_CHAR16:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_Char16 (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = random.randint (0, 0xFFFF)
    v2 = MI_Char16 (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_Char16 (None)
    t3 = MI_Char16 ()
    if COPY_CTOR:
        v3 = MI_Char16 (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_Char16 (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_Char16 (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_Char16
    t4 = MI_Char16 (random.randint (0, 0xFFFF))
    if COPY_CTOR:
        v4 = MI_Char16 (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_Char16 init failed')
            rval = False
    else:
        try:
            v4 = MI_Char16 (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_Char16 (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_Char16 (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_Char16 ('seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # init to under-range value **error**
    try:
        v8 = MI_Char16 (-1)
    except:
        pass
    else:
        BookEndPrint ('----- init to under-range value failed')
        rval = False

    # init to over-range value **error**
    try:
        v9 = MI_Char16 (0x10000)
    except:
        pass
    else:
        BookEndPrint ('----- init to over-range value failed')
        rval = False

    # assign None to None
    v10 = MI_Char16 ()
    v10.value = None
    if v10.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v11 = MI_Char16 ()
    r11 = random.randint (0, 0xFFFF)
    v11.value = r11
    if v11.value != r11:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_Char16 (None) to None
    v12 = MI_Char16 ()
    t12 = MI_Char16 ()
    if ASSIGN_OP:
        v12.value = t12
        if v12.value != t12.value:
            BookEndPrint ('----- MI_Char16 (None) assignment to None failed')
            rval = false
    else:
        try:
            v12.value = t12
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Char16 to None
    v13 = MI_Char16 ()
    t13 = MI_Char16 (random.randint (0, 0xFFFF))
    if ASSIGN_OP:
        v13.value = t13
        if v13.value != t13.value:
            BookEndPrint ('----- MI_Char16 assignment to None failed')
            rval = false
    else:
        try:
            v13.value = t13
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v14 = MI_Char16 ()
    t14 = MI_Boolean ()
    try:
        v14.value = t14
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v15 = MI_Char16 ()
    t15 = MI_Boolean (False)
    try:
        v15.value = t15
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v16 = MI_Char16 ()
    try:
        v16.value = 'sixteen'
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign under-range value to None **error**
    v17 = MI_Char16 ()
    try:
        v17.value = -1
    except:
        pass
    else:
        BookEndPrint ('----- assign under-range value to None failed')
        rval = False

    # assign over-range value to None **error**
    v18 = MI_Char16 ()
    try:
        v18.value = 0x10000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value to None failed')
        rval = False

    # assign None
    v19 = MI_Char16 (random.randint (0, 0xFFFF))
    v19.value = None
    if v19.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    r20a = random.randint (0, 0xFFFF)
    r20b = random.randint (0, 0xFFFF)
    while r20a == r20b:
        r20b = random.randint (0, 0xFFFF)
    v20 = MI_Char16 (r20a)
    v20.value = r20b
    if v20.value != r20b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_Char16 (None)
    v21 = MI_Char16 (random.randint (0, 0xFFFF))
    t21 = MI_Char16 ()
    if ASSIGN_OP:
        v21.value = t21
        if v21.value != t21.value:
            BookEndPrint ('----- MI_Char16 (None) assignment failed')
            rval = false
    else:
        try:
            v21.value = t21
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_Char16
    r22a = random.randint (0, 0xFFFF)
    r22b = random.randint (0, 0xFFFF)
    while r22a == r22b:
        r22b = random.randint (0, 0xFFFF)
    v22 = MI_Char16 (r22a)
    t22 = MI_Char16 (r22b)
    if ASSIGN_OP:
        v22.value = t22
        if v22.value != t22.value:
            BookEndPrint ('----- MI_Char16 assignment failed')
            rval = false
    else:
        try:
            v22.value = t22
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v23 = MI_Char16 (random.randint (0, 0xFFFF))
    t23 = MI_Boolean ()
    try:
        v23.value = t23
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v24 = MI_Char16 (random.randint (0, 0xFFFF))
    t24 = MI_Boolean (False)
    try:
        v24.value = t24
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v25 = MI_Char16 (random.randint (0, 0xFFFF))
    try:
        v25.value = 'twenty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    # assign under-range value **error**
    v26 = MI_Char16 (random.randint (0, 0xFFFF))
    try:
        v26.value = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign under-range value failed')
        rval = False

    # assign over-range value **error**
    v27 = MI_Char16 (random.randint (0, 0xFFFF))
    try:
        v27.value = 0x10000
    except:
        pass
    else:
        BookEndPrint ('----- assign over-range value failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Char16)')

    return rval


def timestamp_test ():
    be = BookEnd ('timestamp_test')

    rval = True
    
    # init (empty)
    v0 = MI_Timestamp ()
    if v0.getType () != MI_DATETIME:
        BookEndPrint ('----- getType failed')
        rval = False
    if not v0.isTimestamp ():
        BookEndPrint ('----- isTimestamp failed')
        rval = False
    if 0 != v0.year or \
           0 != v0.month or \
           0 != v0.day or \
           0 != v0.hour or \
           0 != v0.minute or \
           0 != v0.second or \
           0 != v0.microseconds or \
           0 != v0.utc:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init (year only)
    y1 = random.randint (0, 0xFFFF)
    v1 = MI_Timestamp (year = y1)
    if y1 != v1.year or \
           0 != v1.month or \
           0 != v1.day or \
           0 != v1.hour or \
           0 != v1.minute or \
           0 != v1.second or \
           0 != v1.microseconds or \
           0 != v1.utc:
        BookEndPrint ('----- init (year only) failed')
        rval = False

    # init (month only)
    m2 = random.randint (1, 12)
    v2 = MI_Timestamp (month = m2)
    if 0 != v2.year or \
           m2 != v2.month or \
           0 != v2.day or \
           0 != v2.hour or \
           0 != v2.minute or \
           0 != v2.second or \
           0 != v2.microseconds or \
           0 != v2.utc:
        BookEndPrint ('----- init (month only) failed')
        rval = False

    # init (day only)
    d3 = random.randint (1, 28)
    v3 = MI_Timestamp (day = d3)
    if 0 != v3.year or \
           0 != v3.month or \
           d3 != v3.day or \
           0 != v3.hour or \
           0 != v3.minute or \
           0 != v3.second or \
           0 != v3.microseconds or \
           0 != v3.utc:
        BookEndPrint ('----- init (day only) failed')
        rval = False

    # init (hour only)
    h4 = random.randint (1, 23)
    v4 = MI_Timestamp (hour = h4)
    if 0 != v4.year or \
           0 != v4.month or \
           0 != v4.day or \
           h4 != v4.hour or \
           0 != v4.minute or \
           0 != v4.second or \
           0 != v4.microseconds or \
           0 != v4.utc:
        BookEndPrint ('----- init (hour only) failed')
        rval = False

    # init (minute only)
    min5 = random.randint (1, 59)
    v5 = MI_Timestamp (minute = min5)
    if 0 != v5.year or \
           0 != v5.month or \
           0 != v5.day or \
           0 != v5.hour or \
           min5 != v5.minute or \
           0 != v5.second or \
           0 != v5.microseconds or \
           0 != v5.utc:
        BookEndPrint ('----- init (minute only) failed')
        rval = False

    # init (second only)
    s6 = random.randint (1, 59)
    v6 = MI_Timestamp (second = s6)
    if 0 != v6.year or \
           0 != v6.month or \
           0 != v6.day or \
           0 != v6.hour or \
           0 != v6.minute or \
           s6 != v6.second or \
           0 != v6.microseconds or \
           0 != v6.utc:
        BookEndPrint ('----- init (second only) failed')
        rval = False

    # init (microseconda only)
    ms7 = random.randint (1, 999)
    v7 = MI_Timestamp (microseconds = ms7)
    if 0 != v7.year or \
           0 != v7.month or \
           0 != v7.day or \
           0 != v7.hour or \
           0 != v7.minute or \
           0 != v7.second or \
           ms7 != v7.microseconds or \
           0 != v7.utc:
        BookEndPrint ('----- init (microseconds only) failed')
        rval = False

    # init (utc only)
    u8 = random.randint (1, 11)
    v8 = MI_Timestamp (utc = u8)
    if 0 != v8.year or \
           0 != v8.month or \
           0 != v8.day or \
           0 != v8.hour or \
           0 != v8.minute or \
           0 != v8.second or \
           0 != v8.microseconds or \
           u8 != v8.utc:
        BookEndPrint ('----- init (utc only) failed')
        rval = False

    # init (all)
    y9 = random.randint (0, 9)
    m9 = random.randint (10, 19)
    d9 = random.randint (20, 29)
    h9 = random.randint (30, 39)
    min9 = random.randint (40, 49)
    s9 = random.randint (50, 59)
    ms9 = random.randint (60, 61)
    u9 = random.randint (70, 79)
    v9 = MI_Timestamp (y9, m9, d9, h9, min9, s9, ms9, u9)
    if y9 != v9.year or \
           m9 != v9.month or \
           d9 != v9.day or \
           h9 != v9.hour or \
           min9 != v9.minute or \
           s9 != v9.second or \
           ms9 != v9.microseconds or \
           u9 != v9.utc:
        BookEndPrint ('----- init (all) failed')
        rval = False
    #BookEndPrint (str (v9))
    
    # init underflow (year)
    try:
        v10 = MI_Timestamp (year = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (year) failed')
        rval = False

    # init overflow (year)
    try:
        v11 = MI_Timestamp (year = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (year) failed')
        rval = False

    # init invalid type (year)
    try:
        v12 = MI_Timestamp (year = 'twelve')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (year) failed')
        rval = False

    # init underflow (month)
    try:
        v13 = MI_Timestamp (month = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (month) failed')
        rval = False

    # init overflow (month)
    try:
        v14 = MI_Timestamp (month = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (month) failed')
        rval = False

    # init invalid type (month)
    try:
        v15 = MI_Timestamp (month = 'fifteen')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (month) failed')
        rval = False

    # init underflow (day)
    try:
        v16 = MI_Timestamp (day = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (day) failed')
        rval = False

    # init overflow (day)
    try:
        v17 = MI_Timestamp (day = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (day) failed')
        rval = False

    # init invalid type (day)
    try:
        v18 = MI_Timestamp (day = 'eighteen')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (day) failed')
        rval = False

    # init underflow (hour)
    try:
        v19 = MI_Timestamp (hour = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (hour) failed')
        rval = False

    # init overflow (hour)
    try:
        v20 = MI_Timestamp (hour = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (hour) failed')
        rval = False

    # init invalid type (hour)
    try:
        v21 = MI_Timestamp (hour = 'twenty-one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (hour) failed')
        rval = False

    # init underflow (minute)
    try:
        v22 = MI_Timestamp (minute = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (minute) failed')
        rval = False

    # init overflow (minute)
    try:
        v23 = MI_Timestamp (minute = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (minute) failed')
        rval = False

    # init invalid type (minute)
    try:
        v24 = MI_Timestamp (minute = 'twenty-four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (minute) failed')
        rval = False

    # init underflow (second)
    try:
        v25 = MI_Timestamp (second = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (second) failed')
        rval = False

    # init overflow (second)
    try:
        v26 = MI_Timestamp (second = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (second) failed')
        rval = False

    # init invalid type (second)
    try:
        v27 = MI_Timestamp (second = 'twenty-seven')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (second) failed')
        rval = False

    # init underflow (microseconds)
    try:
        v28 = MI_Timestamp (microseconds = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (microseconds) failed')
        rval = False

    # init overflow (microseconds)
    try:
        v29 = MI_Timestamp (microseconds = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (microseconds) failed')
        rval = False

    # init invalid type (microseconds)
    try:
        v30 = MI_Timestamp (microseconds = 'thirty')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (microseconds) failed')
        rval = False

    # init underflow (utc)
    try:
        v31 = MI_Timestamp (utc = -0x80000001)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (utc) failed')
        rval = False

    # init overflow (utc)
    try:
        v32 = MI_Timestamp (utc = 0x80000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (utc) failed')
        rval = False

    # init invalid type (utc)
    try:
        v33 = MI_Timestamp (utc = 'thirty')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (utc) failed')
        rval = False

    # set underflow (year)
    v34 = MI_Timestamp ()
    try:
        v34.year = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (year) failed')
        rval = False

    # set overflow (year)
    v35 = MI_Timestamp ()
    try:
        v35.year = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (year) failed')
        rval = False

    # set invalid type (year)
    v36 = MI_Timestamp ()
    try:
        v36.year = 'thirty-six'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (year) failed')
        rval = False

    # set underflow (month)
    v37 = MI_Timestamp ()
    try:
        v37.month = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (month) failed')
        rval = False

    # set overflow (month)
    v38 = MI_Timestamp ()
    try:
        v38.month = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (month) failed')
        rval = False

    # set invalid type (month)
    v39 = MI_Timestamp ()
    try:
        v39.month = 'thirty-nine'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (month) failed')
        rval = False

    # set underflow (day)
    v40 = MI_Timestamp ()
    try:
        v40.day = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (day) failed')
        rval = False

    # set overflow (day)
    v41 = MI_Timestamp ()
    try:
        v41.day = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (day) failed')
        rval = False

    # set invalid type (day)
    v42 = MI_Timestamp ()
    try:
        v42.day = 'forty-two'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (day) failed')
        rval = False

    # set underflow (hour)
    v43 = MI_Timestamp ()
    try:
        v43.hour = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (hour) failed')
        rval = False

    # set overflow (hour)
    v44 = MI_Timestamp ()
    try:
        v44.hour = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (hour) failed')
        rval = False

    # set invalid type (hour)
    v45 = MI_Timestamp ()
    try:
        v45.hour = 'forty-five'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (hour) failed')
        rval = False

    # set underflow (minute)
    v46 = MI_Timestamp ()
    try:
        v46.minute = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (minute) failed')
        rval = False

    # set overflow (minute)
    v47 = MI_Timestamp ()
    try:
        v47.minute = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (minute) failed')
        rval = False

    # set invalid type (minute)
    v48 = MI_Timestamp ()
    try:
        v48.minute = 'forty-eight'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (minute) failed')
        rval = False

    # set underflow (second)
    v49 = MI_Timestamp ()
    try:
        v49.second = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (second) failed')
        rval = False

    # set overflow (second)
    v50 = MI_Timestamp ()
    try:
        v50.second = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (second) failed')
        rval = False

    # set invalid type (second)
    v51 = MI_Timestamp ()
    try:
        v51.second = 'fifty-one'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (second) failed')
        rval = False

    # set underflow (microseconds)
    v52 = MI_Timestamp ()
    try:
        v52.microseconds = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (microseconds) failed')
        rval = False

    # set overflow (microseconds)
    v53 = MI_Timestamp ()
    try:
        v53.microseconds = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (microseconds) failed')
        rval = False

    # set invalid type (microseconds)
    v54 = MI_Timestamp ()
    try:
        v54.microseconds = 'fifty-four'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (microseconds) failed')
        rval = False

    # set underflow (utc)
    v55 = MI_Timestamp ()
    try:
        v55.utc = -0x80000001
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (utc) failed')
        rval = False

    # set overflow (utc)
    v56 = MI_Timestamp ()
    try:
        v56.utc = 0x80000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (utc) failed')
        rval = False

    # set invalid type (utc)
    v57 = MI_Timestamp ()
    try:
        v57.utc = 'fifty-seven'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (utc) failed')
        rval = False

    # set (year)
    v58 = MI_Timestamp ()
    y58 = random.randint (0, 2000)
    v58.year = y58
    if y58 != v58.year or \
           0 != v58.month or \
           0 != v58.day or \
           0 != v58.hour or \
           0 != v58.minute or \
           0 != v58.second or \
           0 != v58.microseconds or \
           0 != v58.utc:
        BookEndPrint ('----- set (year) failed')
        rval = False

    # set (month)
    v59 = MI_Timestamp ()
    m59 = random.randint (1, 12)
    v59.month = m59
    if 0 != v59.year or \
           m59 != v59.month or \
           0 != v59.day or \
           0 != v59.hour or \
           0 != v59.minute or \
           0 != v59.second or \
           0 != v59.microseconds or \
           0 != v59.utc:
        BookEndPrint ('----- set (month) failed')
        rval = False

    # set (day)
    v60 = MI_Timestamp ()
    d60 = random.randint (1, 28)
    v60.day = d60
    if 0 != v60.year or \
           0 != v60.month or \
           d60 != v60.day or \
           0 != v60.hour or \
           0 != v60.minute or \
           0 != v60.second or \
           0 != v60.microseconds or \
           0 != v60.utc:
        BookEndPrint ('----- set (day) failed')
        rval = False

    # set (hour)
    v61 = MI_Timestamp ()
    h61 = random.randint (0, 23)
    v61.hour = h61
    if 0 != v61.year or \
           0 != v61.month or \
           0 != v61.day or \
           h61 != v61.hour or \
           0 != v61.minute or \
           0 != v61.second or \
           0 != v61.microseconds or \
           0 != v61.utc:
        BookEndPrint ('----- set (hour) failed')
        rval = False

    # set (minute)
    v62 = MI_Timestamp ()
    min62 = random.randint (0, 59)
    v62.minute = min62
    if 0 != v62.year or \
           0 != v62.month or \
           0 != v62.day or \
           0 != v62.hour or \
           min62 != v62.minute or \
           0 != v62.second or \
           0 != v62.microseconds or \
           0 != v62.utc:
        BookEndPrint ('----- set (minute) failed')
        rval = False

    # set (second)
    v63 = MI_Timestamp ()
    s63 = random.randint (0, 59)
    v63.second = s63
    if 0 != v63.year or \
           0 != v63.month or \
           0 != v63.day or \
           0 != v63.hour or \
           0 != v63.minute or \
           s63 != v63.second or \
           0 != v63.microseconds or \
           0 != v63.utc:
        BookEndPrint ('----- set (second) failed')
        rval = False

    # set (microseconds)
    v64 = MI_Timestamp ()
    ms64 = random.randint (0, 999)
    v64.microseconds = ms64
    if 0 != v64.year or \
           0 != v64.month or \
           0 != v64.day or \
           0 != v64.hour or \
           0 != v64.minute or \
           0 != v64.second or \
           ms64 != v64.microseconds or \
           0 != v64.utc:
        BookEndPrint ('----- set (microseconds) failed')
        rval = False

    # set (utc)
    v65 = MI_Timestamp ()
    u65 = random.randint (0, 12)
    v65.utc = u65
    if 0 != v65.year or \
           0 != v65.month or \
           0 != v65.day or \
           0 != v65.hour or \
           0 != v65.minute or \
           0 != v65.second or \
           0 != v65.microseconds or \
           u65 != v65.utc:
        BookEndPrint ('----- set (utc) failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Timestamp)')

    return rval


def interval_test ():
    be = BookEnd ('interval_test')

    rval = True
    
    # init (empty)
    v0 = MI_Interval ()
    if v0.getType () != MI_DATETIME:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.isTimestamp ():
        BookEndPrint ('----- isTimestamp failed')
        rval = False
    if 0 != v0.days or \
           0 != v0.hours or \
           0 != v0.minutes or \
           0 != v0.seconds or \
           0 != v0.microseconds:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init (days only)
    d1 = random.randint (1, 28)
    v1 = MI_Interval (days = d1)
    if d1 != v1.days or \
           0 != v1.hours or \
           0 != v1.minutes or \
           0 != v1.seconds or \
           0 != v1.microseconds:
        BookEndPrint ('----- init (days only) failed')
        rval = False

    # init (hours only)
    h2 = random.randint (1, 23)
    v2 = MI_Interval (hours = h2)
    if 0 != v2.days or \
           h2 != v2.hours or \
           0 != v2.minutes or \
           0 != v2.seconds or \
           0 != v2.microseconds:
        BookEndPrint ('----- init (hours only) failed')
        rval = False

    # init (minutes only)
    m3 = random.randint (1, 59)
    v3 = MI_Interval (minutes = m3)
    if 0 != v3.days or \
           0 != v3.hours or \
           m3 != v3.minutes or \
           0 != v3.seconds or \
           0 != v3.microseconds:
        BookEndPrint ('----- init (minutes only) failed')
        rval = False

    # init (seconds only)
    s4 = random.randint (1, 59)
    v4 = MI_Interval (seconds = s4)
    if 0 != v4.days or \
           0 != v4.hours or \
           0 != v4.minutes or \
           s4 != v4.seconds or \
           0 != v4.microseconds:
        BookEndPrint ('----- init (seconds only) failed')
        rval = False

    # init (microseconds only)
    ms5 = random.randint (1, 999)
    v5 = MI_Interval (microseconds = ms5)
    if 0 != v5.days or \
           0 != v5.hours or \
           0 != v5.minutes or \
           0 != v5.seconds or \
           ms5 != v5.microseconds:
        BookEndPrint ('----- init (microseconds only) failed')
        rval = False

    # init (all)
    d6 = random.randint (21, 30)
    h6 = random.randint (31, 40)
    m6 = random.randint (41, 50)
    s6 = random.randint (51, 60)
    ms6 = random.randint (61, 70)
    v6 = MI_Interval (d6, h6, m6, s6, ms6)
    if d6 != v6.days or \
           h6 != v6.hours or \
           m6 != v6.minutes or \
           s6 != v6.seconds or \
           ms6 != v6.microseconds:
        BookEndPrint ('----- init (all) failed')
        rval = False
    #BookEndPrint (str (v6))

    # init underflow (days)
    try:
        v7 = MI_Interval (days = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (days) failed')
        rval = False

    # init overflow (days)
    try:
        v8 = MI_Interval (days = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (days) failed')
        rval = False

    # init invalid type (days)
    try:
        v9 = MI_Interval (days = 'nine')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (days) failed')
        rval = False

    # init underflow (hours)
    try:
        v10 = MI_Interval (hours = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (hours) failed')
        rval = False

    # init overflow (hours)
    try:
        v11 = MI_Interval (hours = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (hours) failed')
        rval = False

    # init invalid type (hours)
    try:
        v12 = MI_Interval (hours = 'twelve')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (hours) failed')
        rval = False

    # init underflow (minutes)
    try:
        v13 = MI_Interval (minutes = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (minutes) failed')
        rval = False

    # init overflow (minutes)
    try:
        v14 = MI_Interval (minutes = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (minutes) failed')
        rval = False

    # init invalid type (minutes)
    try:
        v15 = MI_Interval (minutes = 'fifteen')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (minutes) failed')
        rval = False

    # init underflow (seconds)
    try:
        v16 = MI_Interval (seconds = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (seconds) failed')
        rval = False

    # init overflow (seconds)
    try:
        v17 = MI_Interval (seconds = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (seconds) failed')
        rval = False

    # init invalid type (seconds)
    try:
        v18 = MI_Interval (seconds = 'eighteen')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (second) failed')
        rval = False

    # init underflow (microseconds)
    try:
        v19 = MI_Interval (microseconds = -1)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init underflow (microseconds) failed')
        rval = False

    # init overflow (microseconds)
    try:
        v20 = MI_Interval (microseconds = 0x100000000)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init overflow (microseconds) failed')
        rval = False

    # init invalid type (microseconds)
    try:
        v21 = MI_Interval (microseconds = 'twenty-one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init invalid type (microseconds) failed')
        rval = False

    # set underflow (days)
    v22 = MI_Interval ()
    try:
        v22.days = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (days) failed')
        rval = False

    # set overflow (days)
    v23 = MI_Interval ()
    try:
        v23.days = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (days) failed')
        rval = False

    # set invalid type (days)
    v24 = MI_Interval ()
    try:
        v24.days = 'twenty-four'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (days) failed')
        rval = False

    # set underflow (hours)
    v25 = MI_Interval ()
    try:
        v25.hours = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (hours) failed')
        rval = False

    # set overflow (hours)
    v26 = MI_Interval ()
    try:
        v26.hours = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (hours) failed')
        rval = False

    # set invalid type (hours)
    v27 = MI_Interval ()
    try:
        v27.hours = 'twenty-seven'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (hours) failed')
        rval = False

    # set underflow (minutes)
    v28 = MI_Interval ()
    try:
        v28.minutes = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (minutes) failed')
        rval = False

    # set overflow (minutes)
    v29 = MI_Interval ()
    try:
        v29.minutes = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (minutes) failed')
        rval = False

    # set invalid type (minutes)
    v30 = MI_Interval ()
    try:
        v30.minutes = 'thirty'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (minutes) failed')
        rval = False

    # set underflow (seconds)
    v31 = MI_Interval ()
    try:
        v31.seconds = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (seconds) failed')
        rval = False

    # set overflow (seconds)
    v32 = MI_Interval ()
    try:
        v32.seconds = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (seconds) failed')
        rval = False

    # set invalid type (seconds)
    v33 = MI_Interval ()
    try:
        v33.seconds = 'thirty-three'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (seconds) failed')
        rval = False

    # set underflow (microseconds)
    v34 = MI_Interval ()
    try:
        v34.microseconds = -1
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set underflow (microseconds) failed')
        rval = False

    # set overflow (microseconds)
    v35 = MI_Interval ()
    try:
        v35.microseconds = 0x100000000
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set overflow (microseconds) failed')
        rval = False

    # set invalid type (microseconds)
    v36 = MI_Interval ()
    try:
        v36.microseconds = 'thirty-six'
    except ValueError:
        pass
    else:
        BookEndPrint ('----- set invalid type (microseconds) failed')
        rval = False

    # set (days)
    v37 = MI_Interval ()
    d37 = random.randint (0, 2000)
    v37.days = d37
    if d37 != v37.days or \
           0 != v37.hours or \
           0 != v37.minutes or \
           0 != v37.seconds or \
           0 != v37.microseconds:
        BookEndPrint ('----- set (days) failed')
        rval = False

    # set (hours)
    v38 = MI_Interval ()
    h38 = random.randint (0, 23)
    v38.hours = h38
    if 0 != v38.days or \
           h38 != v38.hours or \
           0 != v38.minutes or \
           0 != v38.seconds or \
           0 != v38.microseconds:
        BookEndPrint ('----- set (hours) failed')
        rval = False

    # set (minutes)
    v39 = MI_Interval ()
    m39 = random.randint (0, 59)
    v39.minutes = m39
    if 0 != v39.days or \
           0 != v39.hours or \
           m39 != v39.minutes or \
           0 != v39.seconds or \
           0 != v39.microseconds:
        BookEndPrint ('----- set (minutes) failed')
        rval = False

    # set (seconds)
    v40 = MI_Interval ()
    s40 = random.randint (0, 59)
    v40.seconds = s40
    if 0 != v40.days or \
           0 != v40.hours or \
           0 != v40.minutes or \
           s40 != v40.seconds or \
           0 != v40.microseconds:
        BookEndPrint ('----- set (seconds) failed')
        rval = False

    # set (microseconds)
    v40 = MI_Interval ()
    ms40 = random.randint (0, 999)
    v40.microseconds = ms40
    if 0 != v40.days or \
           0 != v40.hours or \
           0 != v40.minutes or \
           0 != v40.seconds or \
           ms40 != v40.microseconds:
        BookEndPrint ('----- set (microseconds) failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Interval)')

    return rval


def string_test ():
    be = BookEnd ('string_test')
    vals = [
        'apple', 'banana', 'peach', 'pear', 'orange',
        'watermelon', 'lemon', 'grapefruit', 'kiwi', 'plum',
        'chicken', 'dog', 'cat', 'goat', 'sheep',
        'rabbit', 'cow', 'horse', 'llama', 'pig'
        ]

    rval = True

    # init (empty)
    v0 = MI_String ()
    if v0.getType () != MI_STRING:
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.value is not None:
        BookEndPrint ('----- empty init failed')
        rval = False

    # init to None
    v1 = MI_String (None)
    if v1.value is not None:
        BookEndPrint ('----- NULL init failed')
        rval = False
    
    # init to value
    r2 = vals[random.randint (0, len (vals) - 1)]
    v2 = MI_String (r2)
    if v2.value != r2:
        BookEndPrint ('----- value init failed')
        rval = False

    # init to MI_String (None)
    t3 = MI_String ()
    if COPY_CTOR:
        v3 = MI_String (t3)
        if v3.value != t3.value:
            BookEndPrint ('----- MI_String (None) init failed')
            rval = False
    else:
        try:
            v3 = MI_String (t3)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to MI_String
    t4 = MI_String (vals[random.randint (0, len (vals) - 1)])
    if COPY_CTOR:
        v4 = MI_String (t4)
        if v4.value != t4.value:
            BookEndPrint ('----- MI_String init failed')
            rval = False
    else:
        try:
            v4 = MI_String (t4)
        except ValueError:
            pass
        else:
            BookEndPrint ('----- init using copy ctor failed')
            rval = False

    # init to a different MI type (None) **error**
    t5 = MI_Boolean ()
    try:
        v5 = MI_String (t5)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type (None) failed')
        rval = False

    # init to a different MI type **error**
    t6 = MI_Boolean (True)
    try:
        v6 = MI_String (t6)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to a different MI type failed')
        rval = False
        
    # init to invalid literal value **error**
    try:
        v7 = MI_String (True)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False

    # assign None to None
    v8 = MI_String ()
    v8.value = None
    if v8.value is not None:
        BookEndPrint ('----- None assignment to None failed')
        rval = false

    # assign a  value to None
    v9 = MI_String ()
    r9 = vals[random.randint (0, len (vals) - 1)]
    v9.value = r9
    if v9.value != r9:
        BookEndPrint ('----- literal value assignment to None failed')
        rval = false

    # assign MI_String (None) to None
    v10 = MI_String ()
    t10 = MI_String ()
    if ASSIGN_OP:
        v10.value = t10
        if v10.value != t10.value:
            BookEndPrint ('----- MI_String (None) assignment to None failed')
            rval = false
    else:
        try:
            v10.value = t10
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_String to None
    v11 = MI_String ()
    t11 = MI_String (vals[random.randint (0, len (vals) - 1)])
    if ASSIGN_OP:
        v11.value = t11
        if v11.value != t11.value:
            BookEndPrint ('----- MI_String assignment to None failed')
            rval = false
    else:
        try:
            v11.value = t11
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) to None **error**
    v12 = MI_String ()
    t12 = MI_Boolean ()
    try:
        v12.value = t12
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False
    
    # assign a different MI type to None **error**
    v13 = MI_String ()
    t13 = MI_Boolean (False)
    try:
        v13.value = t13
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal to None **error**
    v14 = MI_String ()
    try:
        v14.value = False
    except:
        pass
    else:
        BookEndPrint ('----- MI_Boolean assign invalid literal failed')
        rval = False

    # assign None
    v15 = MI_String (vals[random.randint (0, len (vals) - 1)])
    v15.value = None
    if v15.value is not None:
        BookEndPrint ('----- None assignment failed')
        rval = false

    # assign a literal value
    i16 = random.randint (0, len (vals) - 2)
    r16a = vals[i16]
    r16b = vals[i16 + 1]
    v16 = MI_String (r16a)
    v16.value = r16b
    if v16.value != r16b:
        BookEndPrint ('----- value assignment failed')
        rval = false

    # assign MI_String (None)
    v17 = MI_String (vals[random.randint (0, len (vals) - 1)])
    t17 = MI_String ()
    if ASSIGN_OP:
        v17.value = t17
        if v17.value != t17.value:
            BookEndPrint ('----- MI_String (None) assignment failed')
            rval = false
    else:
        try:
            v17.value = t17
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False

    # assign MI_String
    i18 = random.randint (0, len (vals) - 2)
    r18a = vals[i18]
    r18b = vals[i18 + 1]
    #r22a = random.randint (0, 0xFFFF)
    #r22b = random.randint (0, 0xFFFF)
    #while r22a == r22b:
    #    r22b = random.randint (0, 0xFFFF)
    v18 = MI_String (r18a)
    t18 = MI_String (r18b)
    if ASSIGN_OP:
        v18.value = t18
        if v18.value != t18.value:
            BookEndPrint ('----- MI_String assignment failed')
            rval = false
    else:
        try:
            v18.value = t18
        except ValueError:
            pass
        else:
            BookEndPrint ('----- assignment operator failed')
            rval = False
    
    # assign a different MI type (None) **error**
    v19 = MI_String (vals[random.randint (0, len (vals) - 1)])
    t19 = MI_Boolean ()
    try:
        v19.value = t19
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type (None) failed')
        rval = False

    # assign a different MI type **error**
    v20 = MI_String (vals[random.randint (0, len (vals) - 1)])
    t20 = MI_Boolean (False)
    try:
        v20.value = t20
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign a different MI type failed')
        rval = False

    # assign invalid literal **error**
    v21 = MI_String (vals[random.randint (0, len (vals) - 1)])
    try:
        v21.value = False
    except ValueError:
        pass
    else:
        BookEndPrint ('----- assign invalid literal failed')
        rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_String)')

    return rval


def booleana_test ():
    be = BookEnd ('booleana_test')

    val0 = False if 0 == random.randint (0, 1) else True
    val1 = False if 0 == random.randint (0, 1) else True
    val2 = False if 0 == random.randint (0, 1) else True
    val3 = False if 0 == random.randint (0, 1) else True
    val4 = False if 0 == random.randint (0, 1) else True
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_BooleanA ()
    if MI_BOOLEANA != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_BooleanA ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_BooleanA ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_BooleanA (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_BooleanA (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_BooleanA ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_BooleanA ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_BooleanA ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_BooleanA ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_BooleanA ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_BooleanA ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_BooleanA ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_BooleanA ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_BooleanA ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_BooleanA ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_BooleanA ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_BooleanA ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_BooleanA ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_BooleanA (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_BooleanA ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_BooleanA)')

    return rval


def uint8a_test ():
    be = BookEnd ('uint8a_test')

    val0 = random.randint (0, 0xFF)
    val1 = random.randint (0, 0xFF)
    while val0 == val1:
        val1 = random.randint (0, 0xFF)
    val2 = random.randint (0, 0xFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (0, 0xFF)
    val3 = random.randint (0, 0xFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (0, 0xFF)
    val4 = random.randint (0, 0xFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (0, 0xFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Uint8A ()
    if MI_UINT8A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Uint8A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Uint8A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Uint8A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Uint8A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Uint8A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Uint8A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Uint8A ([val0, -1, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Uint8A ([val0, 0x100, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Uint8A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Uint8A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Uint8A ((val0, -1, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Uint8A ((val0, 0x100, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Uint8A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Uint8A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -1)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x100)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Uint8A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-1)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x100)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Uint8A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Uint8A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -1)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x100)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Uint8A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Uint8A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Uint8A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Uint8A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Uint8A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Uint8A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -1
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x100
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint8A)')

    return rval


def sint8a_test ():
    be = BookEnd ('sint8a_test')

    val0 = random.randint (-0x80, 0x7F)
    val1 = random.randint (-0x80, 0x7F)
    while val0 == val1:
        val1 = random.randint (-0x80, 0x7F)
    val2 = random.randint (-0x80, 0x7F)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (-0x80, 0x7F)
    val3 = random.randint (-0x80, 0x7F)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (-0x80, 0x7F)
    val4 = random.randint (-0x80, 0x7F)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (-0x80, 0x7F)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Sint8A ()
    if MI_SINT8A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Sint8A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Sint8A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Sint8A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Sint8A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Sint8A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Sint8A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Sint8A ([val0, -0x81, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Sint8A ([val0, 0x80, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Sint8A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Sint8A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Sint8A ((val0, -0x81, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Sint8A ((val0, 0x80, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Sint8A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Sint8A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -0x81)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x80)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Sint8A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-0x81)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x80)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Sint8A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Sint8A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -0x81)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x80)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Sint8A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Sint8A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Sint8A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Sint8A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Sint8A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Sint8A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -0x81
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x80
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint8A)')

    return rval


def uint16a_test ():
    be = BookEnd ('uint16a_test')

    val0 = random.randint (0, 0xFFFF)
    val1 = random.randint (0, 0xFFFF)
    while val0 == val1:
        val1 = random.randint (0, 0xFFFF)
    val2 = random.randint (0, 0xFFFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (0, 0xFFFF)
    val3 = random.randint (0, 0xFFFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (0, 0xFFFF)
    val4 = random.randint (0, 0xFFFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (0, 0xFFFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Uint16A ()
    if MI_UINT16A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Uint16A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Uint16A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Uint16A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Uint16A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Uint16A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Uint16A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Uint16A ([val0, -1, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Uint16A ([val0, 0x10000, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Uint16A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Uint16A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Uint16A ((val0, -1, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Uint16A ((val0, 0x10000, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Uint16A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Uint16A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -1)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x10000)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Uint16A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-1)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x10000)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Uint16A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Uint16A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -1)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x10000)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Uint16A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Uint16A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Uint16A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Uint16A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Uint16A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Uint16A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -1
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x10000
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint16A)')

    return rval


def sint16a_test ():
    be = BookEnd ('sint16a_test')

    val0 = random.randint (-0x8000, 0x7FFF)
    val1 = random.randint (-0x8000, 0x7FFF)
    while val0 == val1:
        val1 = random.randint (-0x8000, 0x7FFF)
    val2 = random.randint (-0x8000, 0x7FFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (-0x8000, 0x7FFF)
    val3 = random.randint (-0x8000, 0x7FFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (-0x8000, 0x7FFF)
    val4 = random.randint (-0x8000, 0x7FFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (-0x8000, 0x7FFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Sint16A ()
    if MI_SINT16A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Sint16A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Sint16A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Sint16A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Sint16A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Sint16A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Sint16A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Sint16A ([val0, -0x8001, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Sint16A ([val0, 0x8000, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Sint16A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Sint16A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Sint16A ((val0, -0x8001, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Sint16A ((val0, 0x8000, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Sint16A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Sint16A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -0x8001)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x8000)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Sint16A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-0x8001)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x8000)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Sint16A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Sint16A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -0x8001)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x8000)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Sint16A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Sint16A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Sint16A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Sint16A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Sint16A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Sint16A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -0x8001
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x8000
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint16A)')

    return rval


def uint32a_test ():
    be = BookEnd ('uint32a_test')

    val0 = random.randint (0, 0xFFFFFFFF)
    val1 = random.randint (0, 0xFFFFFFFF)
    while val0 == val1:
        val1 = random.randint (0, 0xFFFFFFFF)
    val2 = random.randint (0, 0xFFFFFFFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (0, 0xFFFFFFFF)
    val3 = random.randint (0, 0xFFFFFFFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (0, 0xFFFFFFFF)
    val4 = random.randint (0, 0xFFFFFFFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (0, 0xFFFFFFFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Uint32A ()
    if MI_UINT32A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Uint32A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Uint32A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Uint32A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Uint32A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Uint32A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Uint32A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Uint32A ([val0, -1, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Uint32A ([val0, 0x100000000, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Uint32A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Uint32A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Uint32A ((val0, -1, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Uint32A ((val0, 0x100000000, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Uint32A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Uint32A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -1)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x100000000)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Uint32A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-1)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x100000000)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Uint32A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Uint32A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -1)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x100000000)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Uint32A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Uint32A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Uint32A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Uint32A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Uint32A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Uint32A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -1
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x100000000
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint32A)')

    return rval


def sint32a_test ():
    be = BookEnd ('sint32a_test')

    val0 = random.randint (-0x80000000, 0x7FFFFFFF)
    val1 = random.randint (-0x80000000, 0x7FFFFFFF)
    while val0 == val1:
        val1 = random.randint (-0x80000000, 0x7FFFFFFF)
    val2 = random.randint (-0x80000000, 0x7FFFFFFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (-0x80000000, 0x7FFFFFFF)
    val3 = random.randint (-0x80000000, 0x7FFFFFFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (-0x80000000, 0x7FFFFFFF)
    val4 = random.randint (-0x80000000, 0x7FFFFFFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (-0x80000000, 0x7FFFFFFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Sint32A ()
    if MI_SINT32A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Sint32A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Sint32A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Sint32A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Sint32A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Sint32A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Sint32A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Sint32A ([val0, -0x80000001, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Sint32A ([val0, 0x80000000, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Sint32A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Sint32A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Sint32A ((val0, -0x80000001, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Sint32A ((val0, 0x80000000, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Sint32A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Sint32A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -0x80000001)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x80000000)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Sint32A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-0x80000001)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x80000000)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Sint32A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Sint32A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -0x80000001)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x80000000)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Sint32A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Sint32A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Sint32A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Sint32A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Sint32A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Sint32A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -0x80000001
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x80000000
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint32A)')

    return rval


def uint64a_test ():
    be = BookEnd ('uint64a_test')

    val0 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    val1 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while val0 == val1:
        val1 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    val2 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    val3 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    val4 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Uint64A ()
    if MI_UINT64A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Uint64A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Uint64A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Uint64A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Uint64A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Uint64A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Uint64A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Uint64A ([val0, -1, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Uint64A ([val0, 0x10000000000000000, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Uint64A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Uint64A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Uint64A ((val0, -1, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Uint64A ((val0, 0x10000000000000000, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Uint64A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Uint64A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -1)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x10000000000000000)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Uint64A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-1)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x10000000000000000)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Uint64A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Uint64A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -1)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x10000000000000000)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Uint64A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Uint64A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Uint64A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Uint64A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Uint64A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Uint64A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -1
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x10000000000000000
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Uint64A)')

    return rval


def sint64a_test ():
    be = BookEnd ('sint64a_test')

    val0 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    val1 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while val0 == val1:
        val1 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    val2 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    val3 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    val4 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Sint64A ()
    if MI_SINT64A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Sint64A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Sint64A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Sint64A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Sint64A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Sint64A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Sint64A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Sint64A ([val0, -0x8000000000000001, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Sint64A ([val0, 0x8000000000000000, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Sint64A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Sint64A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Sint64A ((val0, -0x8000000000000001, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Sint64A ((val0, 0x8000000000000000, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Sint64A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Sint64A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -0x8000000000000001)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x8000000000000000)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Sint64A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-0x8000000000000001)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x8000000000000000)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Sint64A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Sint64A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -0x8000000000000001)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x8000000000000000)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Sint64A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Sint64A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Sint64A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Sint64A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Sint64A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Sint64A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -0x8000000000000001
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x8000000000000000
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Sint64A)')

    return rval


def real32a_test ():
    be = BookEnd ('real32a_test')

    val0 = ctypes.c_float (random.uniform (-1e37, 1e37))
    val1 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (val0.value, val1.value):
        val1 = ctypes.c_float (random.uniform (-1e37, 1e37))
    val2 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (val0.value, val2.value) or \
              float_eq (val1.value, val2.value):
        val2 = ctypes.c_float (random.uniform (-1e37, 1e37))
    val3 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (val0.value, val3.value) or \
              float_eq (val1.value, val3.value) or \
              float_eq (val2.value, val3.value):
        val3 = ctypes.c_float (random.uniform (-1e37, 1e37))
    val4 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (val0.value, val4.value) or \
              float_eq (val1.value, val4.value) or \
              float_eq (val2.value, val4.value) or \
              float_eq (val3.value, val4.value):
        val4 = ctypes.c_float (random.uniform (-1e37, 1e37))
    
    #BookEndPrint ('val0: {0}'.format (val0.value))
    #BookEndPrint ('val1: {0}'.format (val1.value))
    #BookEndPrint ('val2: {0}'.format (val2.value))
    #BookEndPrint ('val3: {0}'.format (val3.value))
    #BookEndPrint ('val4: {0}'.format (val4.value))

    rval = True

    # init (empty)
    v0 = MI_Real32A ()
    if MI_REAL32A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Real32A ([val0.value, val1.value, val2.value])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if not float_eq (v1.getValueAt (0), val0.value) or \
           not float_eq (v1.getValueAt (1), val1.value) or \
           not float_eq (v1.getValueAt (2), val2.value) or \
           not float_eq (v1.getValueAt (-3), val0.value) or \
           not float_eq (v1.getValueAt (-2), val1.value) or \
           not float_eq (v1.getValueAt (-1), val2.value):
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Real32A ((val0.value, val1.value, val2.value))
    if v2.count () != 3 or \
           not float_eq (v2.getValueAt (0), val0.value) or \
           not float_eq (v2.getValueAt (1), val1.value) or \
           not float_eq (v2.getValueAt (2), val2.value):
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Real32A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Real32A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Real32A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Real32A ([val0.value, None, val2.value])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Real32A ([val0.value, -1e39, val2.value])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Real32A ([val0.value, 1e39, val2.value])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Real32A ([val0.value, 'eight', val2.value])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Real32A ((val0.value, None, val2.value))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Real32A ((val0.value, -1e39, val2.value))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Real32A ((val0.value, 1e39, val2.value))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Real32A ((val0.value, 'twelve', val2.value))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Real32A ((val0.value, val1.value, val2.value))
    v13.setValueAt (0, val4.value)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4.value) or \
           not float_eq (v13.getValueAt (1), val1.value) or \
           not float_eq (v13.getValueAt (2), val2.value):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0.value)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4.value) or \
           not float_eq (v13.getValueAt (1), val0.value) or \
           not float_eq (v13.getValueAt (2), val2.value):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1.value)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4.value) or \
           not float_eq (v13.getValueAt (1), val0.value) or \
           not float_eq (v13.getValueAt (2), val1.value):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2.value)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4.value) or \
           not float_eq (v13.getValueAt (1), val0.value) or \
           not float_eq (v13.getValueAt (2), val2.value):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1.value)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4.value) or \
           not float_eq (v13.getValueAt (1), val1.value) or \
           not float_eq (v13.getValueAt (2), val2.value):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0.value)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val0.value) or \
           not float_eq (v13.getValueAt (1), val1.value) or \
           not float_eq (v13.getValueAt (2), val2.value):
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3.value)
    except IndexError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0.value) or \
               not float_eq (v13.getValueAt (1), val1.value) or \
               not float_eq (v13.getValueAt (2), val2.value):
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3.value)
    except IndexError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0.value) or \
               not float_eq (v13.getValueAt (1), val1.value) or \
               not float_eq (v13.getValueAt (2), val2.value):
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3.value)
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0.value) or \
               not float_eq (v13.getValueAt (1), val1.value) or \
               not float_eq (v13.getValueAt (2), val2.value):
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -1e39)
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0.value) or \
               not float_eq (v13.getValueAt (1), val1.value) or \
               not float_eq (v13.getValueAt (2), val2.value):
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 1e39)
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0.value) or \
               not float_eq (v13.getValueAt (1), val1.value) or \
               not float_eq (v13.getValueAt (2), val2.value):
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0.value) or \
               not float_eq (v13.getValueAt (1), val1.value) or \
               not float_eq (v13.getValueAt (2), val2.value):
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Real32A ()
    v14.append (val0.value)
    if v14.count () != 1 or \
           not float_eq (v14.getValueAt (0), val0.value):
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1.value)
    if v14.count () != 2 or \
           not float_eq (v14.getValueAt (0), val0.value) or \
           not float_eq (v14.getValueAt (1), val1.value):
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2.value)
    if v14.count () != 3 or \
           not float_eq (v14.getValueAt (0), val0.value) or \
           not float_eq (v14.getValueAt (1), val1.value) or \
           not float_eq (v14.getValueAt (2), val2.value):
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-1e39)
    except ValueError:
        if v14.count () != 3 or \
               not float_eq (v14.getValueAt (0), val0.value) or \
               not float_eq (v14.getValueAt (1), val1.value) or \
               not float_eq (v14.getValueAt (2), val2.value):
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (1e39)
    except ValueError:
        if v14.count () != 3 or \
               not float_eq (v14.getValueAt (0), val0.value) or \
               not float_eq (v14.getValueAt (1), val1.value) or \
               not float_eq (v14.getValueAt (2), val2.value):
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               not float_eq (v14.getValueAt (0), val0.value) or \
               not float_eq (v14.getValueAt (1), val1.value) or \
               not float_eq (v14.getValueAt (2), val2.value):
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Real32A ()
    v15.insert (0, val1.value)
    if v15.count () != 1 or \
           not float_eq (v15.getValueAt (0), val1.value):
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0.value)
    if v15.count () != 2 or \
           not float_eq (v15.getValueAt (0), val0.value) or \
           not float_eq (v15.getValueAt (1), val1.value):
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3.value)
    if v15.count () != 3 or \
           not float_eq (v15.getValueAt (0), val0.value) or \
           not float_eq (v15.getValueAt (1), val1.value) or \
           not float_eq (v15.getValueAt (2), val3.value):
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2.value)
    if v15.count () != 4 or \
           not float_eq (v15.getValueAt (0), val0.value) or \
           not float_eq (v15.getValueAt (1), val1.value) or \
           not float_eq (v15.getValueAt (2), val2.value) or \
           not float_eq (v15.getValueAt (3), val3.value):
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Real32A ([val2.value])
    v16.insert (-1, val0.value)
    if v16.count () != 2 or \
           not float_eq (v16.getValueAt (0), val0.value) or \
           not float_eq (v16.getValueAt (1), val2.value):
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1.value)
    if v16.count () != 3 or \
           not float_eq (v16.getValueAt (0), val0.value) or \
           not float_eq (v16.getValueAt (1), val1.value) or \
           not float_eq (v16.getValueAt (2), val2.value):
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3.value)
    except IndexError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0.value) or \
               not float_eq (v16.getValueAt (1), val1.value) or \
               not float_eq (v16.getValueAt (2), val2.value):
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3.value)
    except IndexError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0.value) or \
               not float_eq (v16.getValueAt (1), val1.value) or \
               not float_eq (v16.getValueAt (2), val2.value):
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3.value)
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0.value) or \
               not float_eq (v16.getValueAt (1), val1.value) or \
               not float_eq (v16.getValueAt (2), val2.value):
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -1e39)
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0.value) or \
               not float_eq (v16.getValueAt (1), val1.value) or \
               not float_eq (v16.getValueAt (2), val2.value):
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 1e39)
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0.value) or \
               not float_eq (v16.getValueAt (1), val1.value) or \
               not float_eq (v16.getValueAt (2), val2.value):
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0.value) or \
               not float_eq (v16.getValueAt (1), val1.value) or \
               not float_eq (v16.getValueAt (2), val2.value):
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Real32A ((val0.value, val1.value, val2.value, val3.value))
    t17 = v17.pop ()
    if not float_eq (t17, val3.value) or \
           v17.count () != 3 or \
           not float_eq (v17.getValueAt (0), val0.value) or \
           not float_eq (v17.getValueAt (1), val1.value) or \
           not float_eq (v17.getValueAt (2), val2.value):
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if not float_eq (t17, val1.value) or \
           v17.count () != 2 or \
           not float_eq (v17.getValueAt (0), val0.value) or \
           not float_eq (v17.getValueAt (1), val2.value):
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1.value)
    t17 = v17.pop (0)
    if not float_eq (t17, val0.value) or \
           v17.count () != 2 or \
           not float_eq (v17.getValueAt (0), val1.value) or \
           not float_eq (v17.getValueAt (1), val2.value):
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0.value)
    t17 = v17.pop (2)
    if not float_eq (t17, val2.value) or \
           v17.count () != 2 or \
           not float_eq (v17.getValueAt (0), val0.value) or \
           not float_eq (v17.getValueAt (1), val1.value):
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Real32A ((val0.value, val1.value, val2.value))
    t18 = v18.pop (-2)
    if not float_eq (t18, val1.value) or \
           v18.count () != 2 or \
           not float_eq (v18.getValueAt (0), val0.value) or \
           not float_eq (v18.getValueAt (1), val2.value):
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1.value)
    t18 = v18.pop (-3)
    if not float_eq (t18, val0.value) or \
           v18.count () != 2 or \
           not float_eq (v18.getValueAt (0), val1.value) or \
           not float_eq (v18.getValueAt (1), val2.value):
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0.value)
    t18 = v18.pop (-1)
    if not float_eq (t18, val2.value) or \
           v18.count () != 2 or \
           not float_eq (v18.getValueAt (0), val0.value) or \
           not float_eq (v18.getValueAt (1), val1.value):
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Real32A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Real32A ((val0.value, val1.value, val2.value))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               not float_eq (v20.getValueAt (0), val0.value) or \
               not float_eq (v20.getValueAt (1), val1.value) or \
               not float_eq (v20.getValueAt (2), val2.value):
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               not float_eq (v20.getValueAt (0), val0.value) or \
               not float_eq (v20.getValueAt (1), val1.value) or \
               not float_eq (v20.getValueAt (2), val2.value):
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               not float_eq (v20.getValueAt (0), val0.value) or \
               not float_eq (v20.getValueAt (1), val1.value) or \
               not float_eq (v20.getValueAt (2), val2.value):
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0.value, val1.value, val2.value, val3.value)
    v21 = MI_Real32A (vals21)
    i = 0
    for v in v21:
        if not float_eq (v.value, vals21[i]):
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Real32A ((val0.value, val1.value, val2.value))
    vals22 = (val1.value, val2.value, val3.value)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           not float_eq (v22.getValueAt (0), val1.value) or \
           not float_eq (v22.getValueAt (1), val2.value) or \
           not float_eq (v22.getValueAt (2), val3.value):
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -1e39
        except ValueError:
            if v22.count () != 3 or \
                   not float_eq (v22.getValueAt (0), val1.value) or \
                   not float_eq (v22.getValueAt (1), val2.value) or \
                   not float_eq (v22.getValueAt (2), val3.value):
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 1e39
        except ValueError:
            if v22.count () != 3 or \
                   not float_eq (v22.getValueAt (0), val1.value) or \
                   not float_eq (v22.getValueAt (1), val2.value) or \
                   not float_eq (v22.getValueAt (2), val3.value):
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   not float_eq (v22.getValueAt (0), val1.value) or \
                   not float_eq (v22.getValueAt (1), val2.value) or \
                   not float_eq (v22.getValueAt (2), val3.value):
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Real32A)')

    return rval


def real64a_test ():
    be = BookEnd ('real64a_test')

    val0 = random.uniform (-1e307, 1e307)
    val1 = random.uniform (-1e307, 1e307)
    while float_eq (val0, val1):
        val1 = random.uniform (-1e307, 1e307)
    val2 = random.uniform (-1e307, 1e307)
    while float_eq (val0, val2) or \
              float_eq (val1, val2):
        val2 = random.uniform (-1e307, 1e307)
    val3 = random.uniform (-1e307, 1e307)
    while float_eq (val0, val3) or \
              float_eq (val1, val3) or \
              float_eq (val2, val3):
        val3 = random.uniform (-1e307, 1e307)
    val4 = random.uniform (-1e307, 1e307)
    while float_eq (val0, val4) or \
              float_eq (val1, val4) or \
              float_eq (val2, val4) or \
              float_eq (val3, val4):
        val4 = random.uniform (-1e307, 1e307)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Real64A ()
    if MI_REAL64A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Real64A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if not float_eq (v1.getValueAt (0), val0) or \
           not float_eq (v1.getValueAt (1), val1) or \
           not float_eq (v1.getValueAt (2), val2) or \
           not float_eq (v1.getValueAt (-3), val0) or \
           not float_eq (v1.getValueAt (-2), val1) or \
           not float_eq (v1.getValueAt (-1), val2):
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Real64A ((val0, val1, val2))
    if v2.count () != 3 or \
           not float_eq (v2.getValueAt (0), val0) or \
           not float_eq (v2.getValueAt (1), val1) or \
           not float_eq (v2.getValueAt (2), val2):
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Real64A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Real64A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Real64A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Real64A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Real64A ([val0, -1e309, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Real64A ([val0, 1e309, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Real64A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Real64A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Real64A ((val0, -1e309, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Real64A ((val0, 1e309, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Real64A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Real64A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4) or \
           not float_eq (v13.getValueAt (1), val1) or \
           not float_eq (v13.getValueAt (2), val2):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4) or \
           not float_eq (v13.getValueAt (1), val0) or \
           not float_eq (v13.getValueAt (2), val2):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4) or \
           not float_eq (v13.getValueAt (1), val0) or \
           not float_eq (v13.getValueAt (2), val1):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4) or \
           not float_eq (v13.getValueAt (1), val0) or \
           not float_eq (v13.getValueAt (2), val2):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val4) or \
           not float_eq (v13.getValueAt (1), val1) or \
           not float_eq (v13.getValueAt (2), val2):
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           not float_eq (v13.getValueAt (0), val0) or \
           not float_eq (v13.getValueAt (1), val1) or \
           not float_eq (v13.getValueAt (2), val2):
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0) or \
               not float_eq (v13.getValueAt (1), val1) or \
               not float_eq (v13.getValueAt (2), val2):
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0) or \
               not float_eq (v13.getValueAt (1), val1) or \
               not float_eq (v13.getValueAt (2), val2):
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0) or \
               not float_eq (v13.getValueAt (1), val1) or \
               not float_eq (v13.getValueAt (2), val2):
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -1e309)
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0) or \
               not float_eq (v13.getValueAt (1), val1) or \
               not float_eq (v13.getValueAt (2), val2):
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 1e309)
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0) or \
               not float_eq (v13.getValueAt (1), val1) or \
               not float_eq (v13.getValueAt (2), val2):
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               not float_eq (v13.getValueAt (0), val0) or \
               not float_eq (v13.getValueAt (1), val1) or \
               not float_eq (v13.getValueAt (2), val2):
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Real64A ()
    v14.append (val0)
    if v14.count () != 1 or \
           not float_eq (v14.getValueAt (0), val0):
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           not float_eq (v14.getValueAt (0), val0) or \
           not float_eq (v14.getValueAt (1), val1):
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           not float_eq (v14.getValueAt (0), val0) or \
           not float_eq (v14.getValueAt (1), val1) or \
           not float_eq (v14.getValueAt (2), val2):
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-1e309)
    except ValueError:
        if v14.count () != 3 or \
               not float_eq (v14.getValueAt (0), val0) or \
               not float_eq (v14.getValueAt (1), val1) or \
               not float_eq (v14.getValueAt (2), val2):
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (1e309)
    except ValueError:
        if v14.count () != 3 or \
               not float_eq (v14.getValueAt (0), val0) or \
               not float_eq (v14.getValueAt (1), val1) or \
               not float_eq (v14.getValueAt (2), val2):
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               not float_eq (v14.getValueAt (0), val0) or \
               not float_eq (v14.getValueAt (1), val1) or \
               not float_eq (v14.getValueAt (2), val2):
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Real64A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           not float_eq (v15.getValueAt (0), val1):
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           not float_eq (v15.getValueAt (0), val0) or \
           not float_eq (v15.getValueAt (1), val1):
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           not float_eq (v15.getValueAt (0), val0) or \
           not float_eq (v15.getValueAt (1), val1) or \
           not float_eq (v15.getValueAt (2), val3):
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           not float_eq (v15.getValueAt (0), val0) or \
           not float_eq (v15.getValueAt (1), val1) or \
           not float_eq (v15.getValueAt (2), val2) or \
           not float_eq (v15.getValueAt (3), val3):
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Real64A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           not float_eq (v16.getValueAt (0), val0) or \
           not float_eq (v16.getValueAt (1), val2):
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           not float_eq (v16.getValueAt (0), val0) or \
           not float_eq (v16.getValueAt (1), val1) or \
           not float_eq (v16.getValueAt (2), val2):
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0) or \
               not float_eq (v16.getValueAt (1), val1) or \
               not float_eq (v16.getValueAt (2), val2):
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0) or \
               not float_eq (v16.getValueAt (1), val1) or \
               not float_eq (v16.getValueAt (2), val2):
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0) or \
               not float_eq (v16.getValueAt (1), val1) or \
               not float_eq (v16.getValueAt (2), val2):
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -1e309)
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0) or \
               not float_eq (v16.getValueAt (1), val1) or \
               not float_eq (v16.getValueAt (2), val2):
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 1e309)
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0) or \
               not float_eq (v16.getValueAt (1), val1) or \
               not float_eq (v16.getValueAt (2), val2):
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               not float_eq (v16.getValueAt (0), val0) or \
               not float_eq (v16.getValueAt (1), val1) or \
               not float_eq (v16.getValueAt (2), val2):
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Real64A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if not float_eq (t17, val3) or \
           v17.count () != 3 or \
           not float_eq (v17.getValueAt (0), val0) or \
           not float_eq (v17.getValueAt (1), val1) or \
           not float_eq (v17.getValueAt (2), val2):
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if not float_eq (t17, val1) or \
           v17.count () != 2 or \
           not float_eq (v17.getValueAt (0), val0) or \
           not float_eq (v17.getValueAt (1), val2):
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if not float_eq (t17, val0) or \
           v17.count () != 2 or \
           not float_eq (v17.getValueAt (0), val1) or \
           not float_eq (v17.getValueAt (1), val2):
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if not float_eq (t17, val2) or \
           v17.count () != 2 or \
           not float_eq (v17.getValueAt (0), val0) or \
           not float_eq (v17.getValueAt (1), val1):
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Real64A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if not float_eq (t18, val1) or \
           v18.count () != 2 or \
           not float_eq (v18.getValueAt (0), val0) or \
           not float_eq (v18.getValueAt (1), val2):
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if not float_eq (t18, val0) or \
           v18.count () != 2 or \
           not float_eq (v18.getValueAt (0), val1) or \
           not float_eq (v18.getValueAt (1), val2):
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if not float_eq (t18, val2) or \
           v18.count () != 2 or \
           not float_eq (v18.getValueAt (0), val0) or \
           not float_eq (v18.getValueAt (1), val1):
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Real64A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Real64A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               not float_eq (v20.getValueAt (0), val0) or \
               not float_eq (v20.getValueAt (1), val1) or \
               not float_eq (v20.getValueAt (2), val2):
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               not float_eq (v20.getValueAt (0), val0) or \
               not float_eq (v20.getValueAt (1), val1) or \
               not float_eq (v20.getValueAt (2), val2):
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               not float_eq (v20.getValueAt (0), val0) or \
               not float_eq (v20.getValueAt (1), val1) or \
               not float_eq (v20.getValueAt (2), val2):
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Real64A (vals21)
    i = 0
    for v in v21:
        if not float_eq (v.value, vals21[i]):
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Real64A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           not float_eq (v22.getValueAt (0), val1) or \
           not float_eq (v22.getValueAt (1), val2) or \
           not float_eq (v22.getValueAt (2), val3):
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -1e309
        except ValueError:
            if v22.count () != 3 or \
                   not float_eq (v22.getValueAt (0), val1) or \
                   not float_eq (v22.getValueAt (1), val2) or \
                   not float_eq (v22.getValueAt (2), val3):
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 1e309
        except ValueError:
            if v22.count () != 3 or \
                   not float_eq (v22.getValueAt (0), val1) or \
                   not float_eq (v22.getValueAt (1), val2) or \
                   not float_eq (v22.getValueAt (2), val3):
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   not float_eq (v22.getValueAt (0), val1) or \
                   not float_eq (v22.getValueAt (1), val2) or \
                   not float_eq (v22.getValueAt (2), val3):
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Real64A)')

    return rval


def char16a_test ():
    be = BookEnd ('char16a_test')

    val0 = random.randint (0, 0xFFFF)
    val1 = random.randint (0, 0xFFFF)
    while val0 == val1:
        val1 = random.randint (0, 0xFFFF)
    val2 = random.randint (0, 0xFFFF)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (0, 0xFFFF)
    val3 = random.randint (0, 0xFFFF)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (0, 0xFFFF)
    val4 = random.randint (0, 0xFFFF)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (0, 0xFFFF)
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_Char16A ()
    if MI_CHAR16A != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_Char16A ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_Char16A ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_Char16A (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_Char16A (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_Char16A ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_Char16A ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (underflow value) **error**
    try:
        v6 = MI_Char16A ([val0, -1, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (underflow value) failed')
        rval = False

    # PyList init (overflow value) **error**
    try:
        v7 = MI_Char16A ([val0, 0x10000, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (overflow value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_Char16A ([val0, 'eight', val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_Char16A ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (underflow value) **error**
    try:
        v10 = MI_Char16A ((val0, -1, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (underflow value) failed')
        rval = False

    # PyTuple init (overflow value) **error**
    try:
        v11 = MI_Char16A ((val0, 0x10000, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (overflow value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_Char16A ((val0, 'twelve', val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_Char16A ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value underflow) **error**
    try:
        v13.setValueAt (1, -1)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value underflow) failed')
        rval = False

    # setValueAt (value overflow)
    try:
        v13.setValueAt (1, 0x10000)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value overflow) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_Char16A ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value underflow) **error**
    try:
        v14.append (-1)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value underflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value underflow) failed')
        rval = False

    # append (value overflow)
    try:
        v14.append (0x10000)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value overflow) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value overflow) failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append ('fourteen')
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_Char16A ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_Char16A ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # insert (value out of range) **error**
    try:
        v16.insert (1, -1)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False
    try:
        v16.insert (1, 0x10000)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value out of range) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 'sixteen')
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_Char16A ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_Char16A ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_Char16A ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_Char16A ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_Char16A (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_Char16A ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (out of range) **error**
    for v in v22:
        try:
            v.value = -1
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False
    for v in v22:
        try:
            v.value = 0x10000
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value out of range) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value out of range) failed')
            rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 'twenty-two'
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_Char16A)')

    return rval


def datetime_eq (left, right):
    if left.isTimestamp () and right.isTimestamp ():
        if left.year == right.year and \
               left.month == right.month and \
               left.day == right.day and \
               left.hour == right.hour and \
               left.minute == right.minute and \
               left.second == right.second and \
               left.microseconds == right.microseconds and \
               left.utc == right.utc:
            return True
        else:
            return False
    elif not left.isTimestamp () and not right.isTimestamp ():
        if left.days == right.days and \
               left.hours == right.hours and \
               left.minutes == right.minutes and \
               left.seconds == right.seconds and \
               left.microseconds == right.microseconds:
            return True
        return False
    else:
        return False


def datetimea_test ():
    be = BookEnd ('datetimea_test')

    ts0 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))
    ts1 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))
    ts2 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))

    i0 = MI_Interval ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49))

    i1 = MI_Interval ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49))

    i2 = MI_Interval ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49))

    rval = True

    # init (empty)
    v0 = MI_DatetimeA ()
    if MI_DATETIMEA != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init (all MI_Timestamp)
    v1 = MI_DatetimeA ([ts0, ts1, ts2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if not datetime_eq (v1.getValueAt (0), ts0) or \
           not datetime_eq (v1.getValueAt (1), ts1) or \
           not datetime_eq (v1.getValueAt (2), ts2) or \
           not datetime_eq (v1.getValueAt (-3), ts0) or \
           not datetime_eq (v1.getValueAt (-2), ts1) or \
           not datetime_eq (v1.getValueAt (-1), ts2):
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False
 
    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # test that getValueAt returns a clone and not a reference
    val1 = v1.getValueAt (1)
    val1.year = val1.year + 1
    if datetime_eq (v1.getValueAt (1), val1):
        BookEndPrint ('----- getValueAt returned a reference')
        rval = False

    # test that the initializer stores a clone and not a reference
    y4 = random.randint (0, 9)
    while y4 == ts0.year:
        y4 = random.randint (0, 9)
    ts0.year = y4
    if datetime_eq (v1.getValueAt (0), ts0):
        BookEndPrint ('----- initializer stored a reference')
        rval = False

    # PyList init (all MI_Interval)
    v2 = MI_DatetimeA ([i0, i1, i2])
    if v2.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if not datetime_eq (v2.getValueAt (0), i0) or \
       not datetime_eq (v2.getValueAt (1), i1) or \
       not datetime_eq (v2.getValueAt (2), i2) or \
       not datetime_eq (v2.getValueAt (-3), i0) or \
       not datetime_eq (v2.getValueAt (-2), i1) or \
       not datetime_eq (v2.getValueAt (-1), i2):
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v2.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v2.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v2.getValueAt ('two')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # test that getValueAt returns a clone and not a reference
    val1 = v2.getValueAt (1)
    val1.days = val1.days + 1
    if datetime_eq (v2.getValueAt (1), val1):
        BookEndPrint ('----- getValueAt returned a reference')
        rval = False

    # test that the initializer stores a clone and not a reference
    d4 = random.randint (0, 9)
    while d4 == i0.days:
        d4 = random.randint (0, 9)
    i0.days = d4
    if datetime_eq (v2.getValueAt (0), i0):
        BookEndPrint ('----- initializer stored a reference')
        rval = False

    # PyList init (mixed MI_Timestamp and MI_Interval)
    v3 = MI_DatetimeA ([ts0, i0, ts1, i1])
    if v3.count () != 4:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if not datetime_eq (v3.getValueAt (0), ts0) or \
       not datetime_eq (v3.getValueAt (1), i0) or \
       not datetime_eq (v3.getValueAt (2), ts1) or \
       not datetime_eq (v3.getValueAt (3), i1) or \
       not datetime_eq (v3.getValueAt (-4), ts0) or \
       not datetime_eq (v3.getValueAt (-3), i0) or \
       not datetime_eq (v3.getValueAt (-2), ts1) or \
       not datetime_eq (v3.getValueAt (-1), i1):
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    #BookEndPrint (str (v3))

    # test getValueAt (out of range) **error**
    try:
        v3.getValueAt (-5)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v3.getValueAt (4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v3.getValueAt ('three')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # test that getValueAt returns a clone and not a reference
    val1 = v3.getValueAt (1)
    val1.days = val1.days + 1
    if datetime_eq (v3.getValueAt (1), val1):
        BookEndPrint ('----- getValueAt returned a reference')
        rval = False

    # test that the initializer stores a clone and not a reference
    y4 = random.randint (0, 9)
    while y4 == ts0.year:
        y4 = random.randint (0, 9)
    ts0.year = y4
    if datetime_eq (v3.getValueAt (0), ts0):
        BookEndPrint ('----- initializer stored a reference')
        rval = False

    # PyTuple init (all MI_Timestamp)
    v4 = MI_DatetimeA ((ts0, ts1, ts2))
    if v4.count () != 3:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    if not datetime_eq (v4.getValueAt (0), ts0) or \
       not datetime_eq (v4.getValueAt (1), ts1) or \
       not datetime_eq (v4.getValueAt (2), ts2) or \
       not datetime_eq (v4.getValueAt (-3), ts0) or \
       not datetime_eq (v4.getValueAt (-2), ts1) or \
       not datetime_eq (v4.getValueAt (-1), ts2):
        BookEndPrint ('----- PyTuple init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v4.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v4.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v4.getValueAt ('four')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # test that getValueAt returns a clone and not a reference
    val1 = v4.getValueAt (1)
    val1.year = val1.year + 1
    if datetime_eq (v4.getValueAt (1), val1):
        BookEndPrint ('----- getValueAt returned a reference')
        rval = False

    # test that the initializer stores a clone and not a reference
    y4 = random.randint (0, 9)
    while y4 == ts0.year:
        y4 = random.randint (0, 9)
    ts0.year = y4
    if datetime_eq (v4.getValueAt (0), ts0):
        BookEndPrint ('----- initializer stored a reference')
        rval = False

    # PyTuple init (all MI_Interval)
    v5 = MI_DatetimeA ((i0, i1, i2))
    if v5.count () != 3:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    if not datetime_eq (v5.getValueAt (0), i0) or \
       not datetime_eq (v5.getValueAt (1), i1) or \
       not datetime_eq (v5.getValueAt (2), i2) or \
       not datetime_eq (v5.getValueAt (-3), i0) or \
       not datetime_eq (v5.getValueAt (-2), i1) or \
       not datetime_eq (v5.getValueAt (-1), i2):
        BookEndPrint ('----- PyTuple init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v5.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v5.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v5.getValueAt ('five')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # test that getValueAt returns a clone and not a reference
    val1 = v5.getValueAt (1)
    val1.days = val1.days + 1
    if datetime_eq (v5.getValueAt (1), val1):
        BookEndPrint ('----- getValueAt returned a reference')
        rval = False

    # test that the initializer stores a clone and not a reference
    d4 = random.randint (0, 9)
    while d4 == i0.days:
        d4 = random.randint (0, 9)
    i0.days = d4
    if datetime_eq (v5.getValueAt (0), i0):
        BookEndPrint ('----- initializer stored a reference')
        rval = False

    # PyTuple init (mixed MI_Timestamp and MI_Interval)
    v6 = MI_DatetimeA ([ts0, i0, ts1, i1])
    if v6.count () != 4:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    if not datetime_eq (v6.getValueAt (0), ts0) or \
       not datetime_eq (v6.getValueAt (1), i0) or \
       not datetime_eq (v6.getValueAt (2), ts1) or \
       not datetime_eq (v6.getValueAt (3), i1) or \
       not datetime_eq (v6.getValueAt (-4), ts0) or \
       not datetime_eq (v6.getValueAt (-3), i0) or \
       not datetime_eq (v6.getValueAt (-2), ts1) or \
       not datetime_eq (v6.getValueAt (-1), i1):
        BookEndPrint ('----- PyTuple init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v6.getValueAt (-5)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v6.getValueAt (4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v6.getValueAt ('six')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # test that getValueAt returns a clone and not a reference
    val1 = v6.getValueAt (1)
    val1.days = val1.days + 1
    if datetime_eq (v6.getValueAt (1), val1):
        BookEndPrint ('----- getValueAt returned a reference')
        rval = False

    # test that the initializer stores a clone and not a reference
    y4 = random.randint (0, 9)
    while y4 == ts0.year:
        y4 = random.randint (0, 9)
    ts0.year = y4
    if datetime_eq (v6.getValueAt (0), ts0):
        BookEndPrint ('----- initializer stored a reference')
        rval = False
    
    # init from None
    v7 = MI_DatetimeA (None)
    if v7.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v8 = MI_DatetimeA ('eight')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v9 = MI_DatetimeA ([ts0, None, i0])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v10 = MI_DatetimeA ([ts0, 'ten', i0])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None)
    try:
        v11 = MI_DatetimeA ((ts0, None, i0))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_DatetimeA ((ts0, 'twelve', i0))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_DatetimeA ((ts0, i0, ts1, i1))
    v13.setValueAt (0, ts2)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts2) or \
           not datetime_eq (v13.getValueAt (1), i0) or \
           not datetime_eq (v13.getValueAt (2), ts1) or \
           not datetime_eq (v13.getValueAt (3), i1):
        BookEndPrint ('----- setValueAt failed')
        rval = False
        
    v13.setValueAt (1, i2)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts2) or \
           not datetime_eq (v13.getValueAt (1), i2) or \
           not datetime_eq (v13.getValueAt (2), ts1) or \
           not datetime_eq (v13.getValueAt (3), i1):
        BookEndPrint ('----- setValueAt failed')
        rval = False
        
    v13.setValueAt (2, i0)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts2) or \
           not datetime_eq (v13.getValueAt (1), i2) or \
           not datetime_eq (v13.getValueAt (2), i0) or \
           not datetime_eq (v13.getValueAt (3), i1):
        BookEndPrint ('----- setValueAt failed')
        rval = False
        
    v13.setValueAt (3, ts0)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts2) or \
           not datetime_eq (v13.getValueAt (1), i2) or \
           not datetime_eq (v13.getValueAt (2), i0) or \
           not datetime_eq (v13.getValueAt (3), ts0):
        BookEndPrint ('----- setValueAt failed')
        rval = False

    v13.setValueAt (-1, i1)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts2) or \
           not datetime_eq (v13.getValueAt (1), i2) or \
           not datetime_eq (v13.getValueAt (2), i0) or \
           not datetime_eq (v13.getValueAt (3), i1):
        BookEndPrint ('----- setValueAt failed')
        rval = False
        
    v13.setValueAt (-2, ts1)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts2) or \
           not datetime_eq (v13.getValueAt (1), i2) or \
           not datetime_eq (v13.getValueAt (2), ts1) or \
           not datetime_eq (v13.getValueAt (3), i1):
        BookEndPrint ('----- setValueAt failed')
        rval = False

    v13.setValueAt (-3, i0)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts2) or \
           not datetime_eq (v13.getValueAt (1), i0) or \
           not datetime_eq (v13.getValueAt (2), ts1) or \
           not datetime_eq (v13.getValueAt (3), i1):
        BookEndPrint ('----- setValueAt failed')
        rval = False

    v13.setValueAt (-4, ts0)
    if v13.count () != 4 or \
           not datetime_eq (v13.getValueAt (0), ts0) or \
           not datetime_eq (v13.getValueAt (1), i0) or \
           not datetime_eq (v13.getValueAt (2), ts1) or \
           not datetime_eq (v13.getValueAt (3), i1):
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-5, ts2)
    except IndexError:
        if v13.count () != 4 or \
               not datetime_eq (v13.getValueAt (0), ts0) or \
               not datetime_eq (v13.getValueAt (1), i0) or \
               not datetime_eq (v13.getValueAt (2), ts1) or \
               not datetime_eq (v13.getValueAt (3), i1):
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    try:
        v13.setValueAt (4, i2)
    except IndexError:
        if v13.count () != 4 or \
               not datetime_eq (v13.getValueAt (0), ts0) or \
               not datetime_eq (v13.getValueAt (1), i0) or \
               not datetime_eq (v13.getValueAt (2), ts1) or \
               not datetime_eq (v13.getValueAt (3), i1):
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', ts2)
    except ValueError:
        if v13.count () != 4 or \
               not datetime_eq (v13.getValueAt (0), ts0) or \
               not datetime_eq (v13.getValueAt (1), i0) or \
               not datetime_eq (v13.getValueAt (2), ts1) or \
               not datetime_eq (v13.getValueAt (3), i1):
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 'thirteen')
    except ValueError:
        if v13.count () != 4 or \
               not datetime_eq (v13.getValueAt (0), ts0) or \
               not datetime_eq (v13.getValueAt (1), i0) or \
               not datetime_eq (v13.getValueAt (2), ts1) or \
               not datetime_eq (v13.getValueAt (3), i1):
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # test that setValueAt stores a clone and not a reference
    y4 = random.randint (0, 9)
    while y4 == ts0.year:
        y4 = random.randint (0, 9)
    ts0.year = y4
    if datetime_eq (v13.getValueAt (0), ts0):
        BookEndPrint ('----- setValueAt stored a reference')
        rval = False

    # insert
    v14 = MI_DatetimeA ()
    v14.insert (0, ts0)
    if v14.count () != 1 or \
           not datetime_eq (v14.getValueAt (0), ts0):
        BookEndPrint ('----- insert failed')
        rval = False
    v14.insert (0, i0)
    if v14.count () != 2 or \
           not datetime_eq (v14.getValueAt (0), i0) or \
           not datetime_eq (v14.getValueAt (1), ts0):
        BookEndPrint ('----- insert failed')
        rval = False
    v14.insert (2, ts1)
    if v14.count () != 3 or \
           not datetime_eq (v14.getValueAt (0), i0) or \
           not datetime_eq (v14.getValueAt (1), ts0) or \
           not datetime_eq (v14.getValueAt (2), ts1):
        BookEndPrint ('----- insert failed')
        rval = False
    v14.insert (2, i1)
    if v14.count () != 4 or \
           not datetime_eq (v14.getValueAt (0), i0) or \
           not datetime_eq (v14.getValueAt (1), ts0) or \
           not datetime_eq (v14.getValueAt (2), i1) or \
           not datetime_eq (v14.getValueAt (3), ts1):
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v15 = MI_DatetimeA ([ts2])
    v15.insert (-1, i2)
    if v15.count () != 2 or \
           not datetime_eq (v15.getValueAt (0), i2) or \
           not datetime_eq (v15.getValueAt (1), ts2):
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v15.insert (-1, ts1)
    if v15.count () != 3 or \
           not datetime_eq (v15.getValueAt (0), i2) or \
           not datetime_eq (v15.getValueAt (1), ts1) or \
           not datetime_eq (v15.getValueAt (2), ts2):
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v15.insert (4, i2)
    except IndexError:
        if v15.count () != 3 or \
               not datetime_eq (v15.getValueAt (0), i2) or \
               not datetime_eq (v15.getValueAt (1), ts1) or \
               not datetime_eq (v15.getValueAt (2), ts2):
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v15.insert (-4, i2)
    except IndexError:
        if v15.count () != 3 or \
               not datetime_eq (v15.getValueAt (0), i2) or \
               not datetime_eq (v15.getValueAt (1), ts1) or \
               not datetime_eq (v15.getValueAt (2), ts2):
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v15.insert ('fifteen', i2)
    except ValueError:
        if v15.count () != 3 or \
               not datetime_eq (v15.getValueAt (0), i2) or \
               not datetime_eq (v15.getValueAt (1), ts1) or \
               not datetime_eq (v15.getValueAt (2), ts2):
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False
    
    # value type invalid
    try:
        v15.insert (1, 'fifteen')
    except ValueError:
        if v15.count () != 3 or \
               not datetime_eq (v15.getValueAt (0), i2) or \
               not datetime_eq (v15.getValueAt (1), ts1) or \
               not datetime_eq (v15.getValueAt (2), ts2):
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False
    
    # pop
    v16 = MI_DatetimeA ((ts0, i0, ts1, i1))
    t16 = v16.pop ()
    if not datetime_eq (t16, i1) or \
           v16.count () != 3 or \
           not datetime_eq (v16.getValueAt (0), ts0) or \
           not datetime_eq (v16.getValueAt (1), i0) or \
           not datetime_eq (v16.getValueAt (2), ts1):
        BookEndPrint ('----- pop failed')
        rval = False
    t16 = v16.pop (1)
    if not datetime_eq (t16, i0) or \
           v16.count () != 2 or \
           not datetime_eq (v16.getValueAt (0), ts0) or \
           not datetime_eq (v16.getValueAt (1), ts1):
        BookEndPrint ('----- pop failed')
        rval = False
    v16.insert (1, i0)
    t16 = v16.pop (0)
    if not datetime_eq (t16, ts0) or \
           v16.count () != 2 or \
           not datetime_eq (v16.getValueAt (0), i0) or \
           not datetime_eq (v16.getValueAt (1), ts1):
        BookEndPrint ('----- pop failed')
        rval = False
    v16.insert (0, ts0)
    t16 = v16.pop (2)
    if not datetime_eq (t16, ts1) or \
           v16.count () != 2 or \
           not datetime_eq (v16.getValueAt (0), ts0) or \
           not datetime_eq (v16.getValueAt (1), i0):
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v17 = MI_DatetimeA ((ts0, i0, ts1))
    t17 = v17.pop (-2)
    if not datetime_eq (t17, i0) or \
           v17.count () != 2 or \
           not datetime_eq (v17.getValueAt (0), ts0) or \
           not datetime_eq (v17.getValueAt (1), ts1):
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, i0)
    t17 = v17.pop (-3)
    if not datetime_eq (t17, ts0) or \
           v17.count () != 2 or \
           not datetime_eq (v17.getValueAt (0), i0) or \
           not datetime_eq (v17.getValueAt (1), ts1):
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, ts0)
    t17 = v17.pop (-1)
    if not datetime_eq (t17, ts1) or \
           v17.count () != 2 or \
           not datetime_eq (v17.getValueAt (0), ts0) or \
           not datetime_eq (v17.getValueAt (1), i0):
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v18 = MI_DatetimeA ()
    try:
        v18.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v19 = MI_DatetimeA ((ts0, i0, ts1))
    try:
        v19.pop (3)
    except IndexError:
        if v19.count () != 3 or \
               not datetime_eq (v19.getValueAt (0), ts0) or \
               not datetime_eq (v19.getValueAt (1), i0) or \
               not datetime_eq (v19.getValueAt (2), ts1):
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v19.pop (-4)
    except IndexError:
        if v19.count () != 3 or \
               not datetime_eq (v19.getValueAt (0), ts0) or \
               not datetime_eq (v19.getValueAt (1), i0) or \
               not datetime_eq (v19.getValueAt (2), ts1):
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v19.pop ('nineteen')
    except ValueError:
        if v19.count () != 3 or \
               not datetime_eq (v19.getValueAt (0), ts0) or \
               not datetime_eq (v19.getValueAt (1), i0) or \
               not datetime_eq (v19.getValueAt (2), ts1):
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False


    # iterator
    # test get value
    vals20 = (ts0, i0, ts1, i1)
    v20 = MI_DatetimeA (vals20)
    i = 0
    for v in v20:
        if not datetime_eq (v.value, vals20[i]):
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v21 = MI_DatetimeA ((ts0, i0, ts1))
    vals21 = (i1, ts2, i2)
    i = 0
    for v in v21:
        v.value = vals21[i]
        i += 1
    if v21.count () != 3 or \
           not datetime_eq (v21.getValueAt (0), i1) or \
           not datetime_eq (v21.getValueAt (1), ts2) or \
           not datetime_eq (v21.getValueAt (2), i2):
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (invalid type)
    for v in v21:
        try:
            v.value = 'twenty-one'
        except ValueError:
            if v21.count () != 3 or \
                   not datetime_eq (v21.getValueAt (0), i1) or \
                   not datetime_eq (v21.getValueAt (1), ts2) or \
                   not datetime_eq (v21.getValueAt (2), i2):
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    # test that setValue stores a clone and not a reference
    y4 = random.randint (0, 9)
    while y4 == ts2.year:
        y4 = random.randint (0, 9)
    ts2.year = y4
    if datetime_eq (v21.getValueAt (1), ts2):
        BookEndPrint ('----- setValue stored a reference')
        rval = False

    # to_str
    #for v in v21:
    #    BookEndPrint (str (v))

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_DatetimeA)')

    return rval


def stringa_test ():
    be = BookEnd ('stringa_test')

    vals = [
        'apple', 'banana', 'peach', 'pear', 'orange',
        'watermelon', 'lemon', 'grapefruit', 'kiwi', 'plum',
        'chicken', 'dog', 'cat', 'goat', 'sheep',
        'rabbit', 'cow', 'horse', 'llama', 'pig'
        ]

    val0 = random.randint (0, len (vals) - 1)
    val1 = random.randint (0, len (vals) -1)
    while val0 == val1:
        val1 = random.randint (0, len (vals) -1)
    val2 = random.randint (0, len (vals) -1)
    while val0 == val2 or val1 == val2:
        val2 = random.randint (0, len (vals) -1)
    val3 = random.randint (0, len (vals) -1)
    while val0 == val3 or val1 == val3 or val2 == val3:
        val3 = random.randint (0, len (vals) -1)
    val4 = random.randint (0, len (vals) -1)
    while val0 == val4 or val1 == val4 or val2 == val4 or val3 == val4:
        val4 = random.randint (0, len (vals) -1)

    val0 = vals[val0]
    val1 = vals[val1]
    val2 = vals[val2]
    val3 = vals[val3]
    val4 = vals[val4]
    
    #BookEndPrint ('val0: {0}'.format (val0))
    #BookEndPrint ('val1: {0}'.format (val1))
    #BookEndPrint ('val2: {0}'.format (val2))
    #BookEndPrint ('val3: {0}'.format (val3))
    #BookEndPrint ('val4: {0}'.format (val4))

    rval = True

    # init (empty)
    v0 = MI_StringA ()
    if MI_STRINGA != v0.getType ():
        BookEndPrint ('----- getType failed')
        rval = False
    if v0.count () != 0:
        BookEndPrint ('----- empty init failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v0.getValueAt (0)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (-1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v0.getValueAt (1)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
        
    # test getValueAt (invalid type) **error**
    try:
        v0.getValueAt ('zero')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (empty - invalid literal) failed')
        rval = False

    # PyList init
    v1 = MI_StringA ([val0, val1, val2])
    if v1.count () != 3:
        BookEndPrint ('----- PyList init failed')
        rval = False
    if v1.getValueAt (0) != val0 or \
           v1.getValueAt (1) != val1 or \
           v1.getValueAt (2) != val2 or \
           v1.getValueAt (-3) != val0 or \
           v1.getValueAt (-2) != val1 or \
           v1.getValueAt (-1) != val2:
        BookEndPrint ('----- PyList init or getValueAt failed')
        rval = False

    # test getValueAt (out of range) **error**
    try:
        v1.getValueAt (-4)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False
    try:
        v1.getValueAt (3)
    except IndexError:
        pass
    else:
        BookEndPrint ('----- getValueAt (out of range) failed')
        rval = False

    # test getValueAt (invalid type) **error**
    try:
        v1.getValueAt ('one')
    except ValueError:
        pass
    else:
        BookEndPrint ('----- getValueAt (invalid type) failed')
        rval = False

    # PyTuple init
    v2 = MI_StringA ((val0, val1, val2))
    if v2.count () != 3 or \
           v2.getValueAt (0) != val0 or \
           v2.getValueAt (1) != val1 or \
           v2.getValueAt (2) != val2:
        BookEndPrint ('----- PyTuple init failed')
        rval = False
    
    # init from None **error**
    #try:
    #    v3 = MI_StringA (None)
    #except ValueError:
    #    pass
    #else:
    #    BookEndPrint ('----- None init failed')
    #    rval = False
    v3 = MI_StringA (None)
    if v3.count () != 0:
        BookEndPrint ('----- None init failed')
        rval = False
    
    # init from invalid literal value **error**
    try:
        v4 = MI_StringA (4)
    except ValueError:
        pass
    else:
        BookEndPrint ('----- init to invalid literal failed')
        rval = False;

    # PyList init (None) **error**
    try:
        v5 = MI_StringA ([val0, None, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (None value) failed')
        rval = False

    # PyList init (invalid type) **error**
    try:
        v8 = MI_StringA ([val0, 8, val2])
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyList init (invalid type) failed')
        rval = False

    # PyTuple init (None) **error**
    try:
        v9 = MI_StringA ((val0, None, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (None value) failed')
        rval = False

    # PyTuple init (invalid type) **error**
    try:
        v12 = MI_StringA ((val0, 12, val2))
    except ValueError:
        pass
    else:
        BookEndPrint ('----- PyTuple init (invalid type) failed')
        rval = False

    # setValueAt
    v13 = MI_StringA ((val0, val1, val2))
    v13.setValueAt (0, val4)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (1, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val1:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-1, val2)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val0 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-2, val1)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val4 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False
    v13.setValueAt (-3, val0)
    if v13.count () != 3 or \
           v13.getValueAt (0) != val0 or \
           v13.getValueAt (1) != val1 or \
           v13.getValueAt (2) != val2:
        BookEndPrint ('----- setValueAt failed')
        rval = False

    # setValueAt (index out of range) **error**
    try:
        v13.setValueAt (-4, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False
    try:
        v13.setValueAt (3, val3)
    except IndexError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index out of range) failed')
        rval = False

    # setValueAt (index invalid type) **error**
    try:
        v13.setValueAt ('one', val3)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (index invalid type) failed')
        rval = False

    # setValueAt (value invalid type) **error**
    try:
        v13.setValueAt (1, 13)
    except ValueError:
        if v13.count () != 3 or \
               v13.getValueAt (0) != val0 or \
               v13.getValueAt (1) != val1 or \
               v13.getValueAt (2) != val2:
            BookEndPrint ('----- setValueAt (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- setValueAt (value invalid type) failed')
        rval = False

    # append
    v14 = MI_StringA ()
    v14.append (val0)
    if v14.count () != 1 or \
           v14.getValueAt (0) != val0:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val1)
    if v14.count () != 2 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1:
        BookEndPrint ('----- append failed')
        rval = False
    v14.append (val2)
    if v14.count () != 3 or \
           v14.getValueAt (0) != val0 or \
           v14.getValueAt (1) != val1 or \
           v14.getValueAt (2) != val2:
        BookEndPrint ('----- append failed')
        rval = False

    # append (value invalid type) **error**
    try:
        v14.append (14)
    except ValueError:
        if v14.count () != 3 or \
               v14.getValueAt (0) != val0 or \
               v14.getValueAt (1) != val1 or \
               v14.getValueAt (2) != val2:
            BookEndPrint ('----- append (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- append (value invalid type) failed')
        rval = False

    # insert
    v15 = MI_StringA ()
    v15.insert (0, val1)
    if v15.count () != 1 or \
           v15.getValueAt (0) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (0, val0)
    if v15.count () != 2 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val3)
    if v15.count () != 3 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
    v15.insert (2, val2)
    if v15.count () != 4 or \
           v15.getValueAt (0) != val0 or \
           v15.getValueAt (1) != val1 or \
           v15.getValueAt (2) != val2 or \
           v15.getValueAt (3) != val3:
        BookEndPrint ('----- insert failed')
        rval = False
        
    # insert using negative indices
    v16 = MI_StringA ([val2])
    v16.insert (-1, val0)
    if v16.count () != 2 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    v16.insert (-1, val1)
    if v16.count () != 3 or \
           v16.getValueAt (0) != val0 or \
           v16.getValueAt (1) != val1 or \
           v16.getValueAt (2) != val2:
        BookEndPrint ('----- insert (negative index) failed')
        rval = False
    
    # insert (index out of bounds) **error**
    try:
        v16.insert (4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False
    try:
        v16.insert (-4, val3)
    except IndexError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index out of bounds) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index out of bounds) failed')
        rval = False

    # insert (index invalid type) **error**
    try:
        v16.insert ('sixteen', val3)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (index invalid type) failed')
        rval = False

    # value type invalid
    try:
        v16.insert (1, 16)
    except ValueError:
        if v16.count () != 3 or \
               v16.getValueAt (0) != val0 or \
               v16.getValueAt (1) != val1 or \
               v16.getValueAt (2) != val2:
            BookEndPrint ('----- insert (value invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- insert (value invalid type) failed')
        rval = False

    # pop
    v17 = MI_StringA ((val0, val1, val2, val3))
    t17 = v17.pop ()
    if t17 != val3 or \
           v17.count () != 3 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1 or \
           v17.getValueAt (2) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    t17 = v17.pop (1)
    if t17 != val1 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (1, val1)
    t17 = v17.pop (0)
    if t17 != val0 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val1 or \
           v17.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v17.insert (0, val0)
    t17 = v17.pop (2)
    if t17 != val2 or \
           v17.count () != 2 or \
           v17.getValueAt (0) != val0 or \
           v17.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (negative indices)
    v18 = MI_StringA ((val0, val1, val2))
    t18 = v18.pop (-2)
    if t18 != val1 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (1, val1)
    t18 = v18.pop (-3)
    if t18 != val0 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val1 or \
           v18.getValueAt (1) != val2:
        BookEndPrint ('----- pop failed')
        rval = False
    v18.insert (0, val0)
    t18 = v18.pop (-1)
    if t18 != val2 or \
           v18.count () != 2 or \
           v18.getValueAt (0) != val0 or \
           v18.getValueAt (1) != val1:
        BookEndPrint ('----- pop failed')
        rval = False

    # pop (empty array) **error**
    v19 = MI_StringA ()
    try:
        v19.pop ()
    except IndexError:
        pass
    else:
        BookEndPrint ('----- pop (empty array) failed')
        rval = False

    v20 = MI_StringA ((val0, val1, val2))
    try:
        v20.pop (3)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False
    try:
        v20.pop (-4)
    except IndexError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index out of range) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index out of range) failed')
        rval = False

    # pop (index invalid type) **error**
    try:
        v20.pop ('twenty')
    except ValueError:
        if v20.count () != 3 or \
               v20.getValueAt (0) != val0 or \
               v20.getValueAt (1) != val1 or \
               v20.getValueAt (2) != val2:
            BookEndPrint ('----- pop (index invalid type) failed')
            rval = False
    else:
        BookEndPrint ('----- pop (index invalid type) failed')
        rval = False

    # test get value
    vals21 = (val0, val1, val2, val3)
    v21 = MI_StringA (vals21)
    i = 0
    for v in v21:
        if v.value != vals21[i]:
            BookEndPrint ('----- iterator (get value) failed')
            rval = False
        i += 1

    # iterator set value
    v22 = MI_StringA ((val0, val1, val2))
    vals22 = (val1, val2, val3)
    i = 0
    for v in v22:
        v.value = vals22[i]
        i += 1
    if v22.count () != 3 or \
           v22.getValueAt (0) != val1 or \
           v22.getValueAt (1) != val2 or \
           v22.getValueAt (2) != val3:
        BookEndPrint ('----- iterator (set value) failed')
        rval = False

    # iterator set value (invalid type)
    for v in v22:
        try:
            v.value = 22
        except ValueError:
            if v22.count () != 3 or \
                   v22.getValueAt (0) != val1 or \
                   v22.getValueAt (1) != val2 or \
                   v22.getValueAt (2) != val3:
                BookEndPrint ('----- iterator (set value invalid type) failed')
                rval = False
        else:
            BookEndPrint ('----- iterator (set value invalid type) failed')
            rval = False

    if not rval:
        BookEndPrint ('!!!!!  Tests have failed! (MI_StringA)')

    return rval


def array_eq (lhs, rhs):
    rval = True
    if lhs.count () == rhs.count ():
        for i in range (lhs.count ()):
            rval = rval and lhs.getValueAt (i) == rhs.getValueAt (i)
    else:
        rval = False
    return rval;


def float_array_eq (lhs, rhs):
    rval = True
    if lhs.count () == rhs.count ():
        for i in range (lhs.count ()):
            rval = rval and float_eq (lhs.getValueAt (i), rhs.getValueAt (i))
    else:
        rval = False
    return rval;


def datetime_array_eq (lhs, rhs):
    rval = True
    if lhs.count () == rhs.count ():
        for i in range (lhs.count ()):
            rval = rval and datetime_eq (lhs.getValueAt (i), rhs.getValueAt (i))
    else:
        rval = False
    return rval;
               

def instance_test ():
    be = BookEnd ('instance_test')

    rval = True

    inst0 = MI_Instance ()

    # bool
    boolValIn = MI_Boolean (True)
    inst0.SetValue ('bool', boolValIn)
    boolValOut = inst0.GetValue ('bool')
    if boolValIn.value != boolValOut.value:
        BookEndPrint ('----- bool SetValue/GetValue failed')
        rval = False
    boolValIn.value = False
    if not boolValOut.value:
        BookEndPrint ('----- bool SetValue/GetValue reference')
        rval = False
    boolValOut.value = False
    if not inst0.GetValue ('bool').value:
        BookEndPrint ('----- bool SetValue/GetValue stored a reference')
        rval = False

    # uint8
    uint8_0 = random.randint (0, 0xFF)
    uint8_1 = random.randint (0, 0xFF)
    uint8_2 = random.randint (0, 0xFF)
    while uint8_1 == uint8_0:
        uint8_1 = random.randint (0, 0xFF)
    while uint8_2 == uint8_0 or \
          uint8_2 == uint8_1:
        uint8_2 = random.randint (0, 0xFF)

    uint8_in = MI_Uint8 (uint8_0)
    inst1 = MI_Instance ()
    
    inst1.SetValue ('uint8', uint8_in)
    uint8_out = inst1.GetValue ('uint8')

    if uint8_out is not None:
        if uint8_in.value != uint8_0 or \
               inst1.GetValue ('uint8').value != uint8_0 or \
               uint8_out.value != uint8_0:
            BookEndPrint ('----- uint8 SetValue/GetValue failed')
            rval = False
        else:   
            uint8_in.value = uint8_1
            if uint8_in.value != uint8_1 or \
                   inst1.GetValue ('uint8').value != uint8_0 or \
                   uint8_out.value != uint8_0:
                BookEndPrint ('----- uint8 SetValue/GetValue stored a reference')
                rval = False
            else:
                uint8_out.value = uint8_2
                if uint8_in.value != uint8_1 or \
                       inst1.GetValue ('uint8').value != uint8_0 or \
                       uint8_out.value != uint8_2:
                    BookEndPrint ('----- uint8 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint8 SetValue/GetValue returned None')
        rval = False

    inst2 = MI_Instance ()
    inst2.SetValue ('uint8', inst1.GetValue ('uint8'))
    if inst2.GetValue ('uint8').value == inst1.GetValue ('uint8').value:
        inst2.SetValue ('uint8', MI_Uint8 (uint8_1))
        if inst2.GetValue ('uint8').value != uint8_1:
            BookEndPrint ("----- uint8  SetValue failed")
            rval = False
        if inst1.GetValue ('uint8').value == uint8_1:
            BookEndPrint ('----- uint8 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint8 SetValue/GetValue failed')
        rval = False

    # sint8
    sint8_0 = random.randint (-0x80, 0x7F)
    sint8_1 = random.randint (-0x80, 0x7F)
    sint8_2 = random.randint (-0x80, 0x7F)
    while sint8_1 == sint8_0:
        sint8_1 = random.randint (-0x80, 0x7F)
    while sint8_2 == sint8_0 or \
          sint8_2 == sint8_1:
        sint8_2 = random.randint (-0x80, 0x7F)

    sint8_in = MI_Sint8 (sint8_0)
    inst3 = MI_Instance ()
    
    inst3.SetValue ('sint8', sint8_in)
    sint8_out = inst3.GetValue ('sint8')

    if sint8_out is not None:
        if sint8_in.value != sint8_0 or \
               inst3.GetValue ('sint8').value != sint8_0 or \
               sint8_out.value != sint8_0:
            BookEndPrint ('----- sint8 SetValue/GetValue failed')
            rval = False
        else:   
            sint8_in.value = sint8_1
            if sint8_in.value != sint8_1 or \
                   inst3.GetValue ('sint8').value != sint8_0 or \
                   sint8_out.value != sint8_0:
                BookEndPrint ('----- sint8 SetValue/GetValue stored a reference')
                rval = False
            else:
                sint8_out.value = sint8_2
                if sint8_in.value != sint8_1 or \
                       inst3.GetValue ('sint8').value != sint8_0 or \
                       sint8_out.value != sint8_2:
                    BookEndPrint ('----- sint8 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint8 SetValue/GetValue returned None')
        rval = False

    inst4 = MI_Instance ()
    inst4.SetValue ('sint8', inst3.GetValue ('sint8'))
    if inst4.GetValue ('sint8').value == inst3.GetValue ('sint8').value:
        inst4.SetValue ('sint8', MI_Sint8 (sint8_1))
        if inst4.GetValue ('sint8').value != sint8_1:
            BookEndPrint ("----- sint8  SetValue failed")
            rval = False
        if inst3.GetValue ('sint8').value == sint8_1:
            BookEndPrint ('----- sint8 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint8 SetValue/GetValue failed')
        rval = False

    # uint16
    uint16_0 = random.randint (0, 0xFFFF)
    uint16_1 = random.randint (0, 0xFFFF)
    uint16_2 = random.randint (0, 0xFFFF)
    while uint16_1 == uint16_0:
        uint16_1 = random.randint (0, 0xFFFF)
    while uint16_2 == uint16_0 or \
          uint16_2 == uint16_1:
        uint16_2 = random.randint (0, 0xFFFF)

    uint16_in = MI_Uint16 (uint16_0)
    inst5 = MI_Instance ()
    
    inst5.SetValue ('uint16', uint16_in)
    uint16_out = inst5.GetValue ('uint16')

    if uint16_out is not None:
        if uint16_in.value != uint16_0 or \
               inst5.GetValue ('uint16').value != uint16_0 or \
               uint16_out.value != uint16_0:
            BookEndPrint ('----- uint16 SetValue/GetValue failed')
            rval = False
        else:   
            uint16_in.value = uint16_1
            if uint16_in.value != uint16_1 or \
                   inst5.GetValue ('uint16').value != uint16_0 or \
                   uint16_out.value != uint16_0:
                BookEndPrint ('----- uint16 SetValue/GetValue stored a reference')
                rval = False
            else:
                uint16_out.value = uint16_2
                if uint16_in.value != uint16_1 or \
                       inst5.GetValue ('uint16').value != uint16_0 or \
                       uint16_out.value != uint16_2:
                    BookEndPrint ('----- uint16 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint16 SetValue/GetValue returned None')
        rval = False

    inst6 = MI_Instance ()
    inst6.SetValue ('uint16', inst5.GetValue ('uint16'))
    if inst6.GetValue ('uint16').value == inst5.GetValue ('uint16').value:
        inst6.SetValue ('uint16', MI_Uint16 (uint16_1))
        if inst6.GetValue ('uint16').value != uint16_1:
            BookEndPrint ("----- uint16  SetValue failed")
            rval = False
        if inst5.GetValue ('uint16').value == uint16_1:
            BookEndPrint ('----- uint16 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint16 SetValue/GetValue failed')
        rval = False

    # sint16
    sint16_0 = random.randint (-0x8000, 0x7FFF)
    sint16_1 = random.randint (-0x8000, 0x7FFF)
    sint16_2 = random.randint (-0x8000, 0x7FFF)
    while sint16_1 == sint16_0:
        sint16_1 = random.randint (-0x8000, 0x7FFF)
    while sint16_2 == sint16_0 or \
          sint16_2 == sint16_1:
        sint16_2 = random.randint (-0x8000, 0x7FFF)

    sint16_in = MI_Sint16 (sint16_0)
    inst7 = MI_Instance ()
    
    inst7.SetValue ('sint16', sint16_in)
    sint16_out = inst7.GetValue ('sint16')

    if sint16_out is not None:
        if sint16_in.value != sint16_0 or \
               inst7.GetValue ('sint16').value != sint16_0 or \
               sint16_out.value != sint16_0:
            BookEndPrint ('----- sint16 SetValue/GetValue failed')
            rval = False
        else:   
            sint16_in.value = sint16_1
            if sint16_in.value != sint16_1 or \
                   inst7.GetValue ('sint16').value != sint16_0 or \
                   sint16_out.value != sint16_0:
                BookEndPrint ('----- sint16 SetValue/GetValue stored a reference')
                rval = False
            else:
                sint16_out.value = sint16_2
                if sint16_in.value != sint16_1 or \
                       inst7.GetValue ('sint16').value != sint16_0 or \
                       sint16_out.value != sint16_2:
                    BookEndPrint ('----- sint16 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint16 SetValue/GetValue returned None')
        rval = False

    inst8 = MI_Instance ()
    inst8.SetValue ('sint16', inst7.GetValue ('sint16'))
    if inst8.GetValue ('sint16').value == inst7.GetValue ('sint16').value:
        inst8.SetValue ('sint16', MI_Sint16 (sint16_1))
        if inst8.GetValue ('sint16').value != sint16_1:
            BookEndPrint ("----- sint16  SetValue failed")
            rval = False
        if inst7.GetValue ('sint16').value == sint16_1:
            BookEndPrint ('----- sint16 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint16 SetValue/GetValue failed')
        rval = False

    # uint32
    uint32_0 = random.randint (0, 0xFFFFFFFF)
    uint32_1 = random.randint (0, 0xFFFFFFFF)
    uint32_2 = random.randint (0, 0xFFFFFFFF)
    while uint32_1 == uint32_0:
        uint32_1 = random.randint (0, 0xFFFFFFFF)
    while uint32_2 == uint32_0 or \
          uint32_2 == uint32_1:
        uint32_2 = random.randint (0, 0xFFFFFFFF)

    uint32_in = MI_Uint32 (uint32_0)
    inst9 = MI_Instance ()
    
    inst9.SetValue ('uint32', uint32_in)
    uint32_out = inst9.GetValue ('uint32')

    if uint32_out is not None:
        if uint32_in.value != uint32_0 or \
               inst9.GetValue ('uint32').value != uint32_0 or \
               uint32_out.value != uint32_0:
            BookEndPrint ('----- uint32 SetValue/GetValue failed')
            rval = False
        else:   
            uint32_in.value = uint32_1
            if uint32_in.value != uint32_1 or \
                   inst9.GetValue ('uint32').value != uint32_0 or \
                   uint32_out.value != uint32_0:
                BookEndPrint ('----- uint32 SetValue/GetValue stored a reference')
                rval = False
            else:
                uint32_out.value = uint32_2
                if uint32_in.value != uint32_1 or \
                       inst9.GetValue ('uint32').value != uint32_0 or \
                       uint32_out.value != uint32_2:
                    BookEndPrint ('----- uint32 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint32 SetValue/GetValue returned None')
        rval = False

    inst10 = MI_Instance ()
    inst10.SetValue ('uint32', inst9.GetValue ('uint32'))
    if inst10.GetValue ('uint32').value == inst9.GetValue ('uint32').value:
        inst10.SetValue ('uint32', MI_Uint32 (uint32_1))
        if inst10.GetValue ('uint32').value != uint32_1:
            BookEndPrint ("----- uint32  SetValue failed")
            rval = False
        if inst9.GetValue ('uint32').value == uint32_1:
            BookEndPrint ('----- uint32 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint32 SetValue/GetValue failed')
        rval = False

    # sint32
    sint32_0 = random.randint (0, 0xFF)
    sint32_1 = random.randint (0, 0xFF)
    sint32_2 = random.randint (0, 0xFF)
    while sint32_1 == sint32_0:
        sint32_1 = random.randint (0, 0xFF)
    while sint32_2 == sint32_0 or \
          sint32_2 == sint32_1:
        sint32_2 = random.randint (0, 0xFF)

    sint32_in = MI_Sint32 (sint32_0)
    inst11 = MI_Instance ()
    
    inst11.SetValue ('sint32', sint32_in)
    sint32_out = inst11.GetValue ('sint32')

    if sint32_out is not None:
        if sint32_in.value != sint32_0 or \
               inst11.GetValue ('sint32').value != sint32_0 or \
               sint32_out.value != sint32_0:
            BookEndPrint ('----- sint32 SetValue/GetValue failed')
            rval = False
        else:   
            sint32_in.value = sint32_1
            if sint32_in.value != sint32_1 or \
                   inst11.GetValue ('sint32').value != sint32_0 or \
                   sint32_out.value != sint32_0:
                BookEndPrint ('----- sint32 SetValue/GetValue stored a reference')
                rval = False
            else:
                sint32_out.value = sint32_2
                if sint32_in.value != sint32_1 or \
                       inst11.GetValue ('sint32').value != sint32_0 or \
                       sint32_out.value != sint32_2:
                    BookEndPrint ('----- sint32 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint32 SetValue/GetValue returned None')
        rval = False

    inst12 = MI_Instance ()
    inst12.SetValue ('sint32', inst11.GetValue ('sint32'))
    if inst12.GetValue ('sint32').value == inst11.GetValue ('sint32').value:
        inst12.SetValue ('sint32', MI_Sint32 (sint32_1))
        if inst12.GetValue ('sint32').value != sint32_1:
            BookEndPrint ("----- sint32  SetValue failed")
            rval = False
        if inst11.GetValue ('sint32').value == sint32_1:
            BookEndPrint ('----- sint32 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint32 SetValue/GetValue failed')
        rval = False

    # uint64
    uint64_0 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    uint64_1 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    uint64_2 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_1 == uint64_0:
        uint64_1 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_2 == uint64_0 or \
          uint64_2 == uint64_1:
        uint64_2 = random.randint (0, 0xFFFFFFFFFFFFFFFF)

    uint64_in = MI_Uint64 (uint64_0)
    inst13 = MI_Instance ()
    
    inst13.SetValue ('uint64', uint64_in)
    uint64_out = inst13.GetValue ('uint64')

    if uint64_out is not None:
        if uint64_in.value != uint64_0 or \
               inst13.GetValue ('uint64').value != uint64_0 or \
               uint64_out.value != uint64_0:
            BookEndPrint ('----- uint64 SetValue/GetValue failed')
            rval = False
        else:   
            uint64_in.value = uint64_1
            if uint64_in.value != uint64_1 or \
                   inst13.GetValue ('uint64').value != uint64_0 or \
                   uint64_out.value != uint64_0:
                BookEndPrint ('----- uint64 SetValue/GetValue stored a reference')
                rval = False
            else:
                uint64_out.value = uint64_2
                if uint64_in.value != uint64_1 or \
                       inst13.GetValue ('uint64').value != uint64_0 or \
                       uint64_out.value != uint64_2:
                    BookEndPrint ('----- uint64 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint64 SetValue/GetValue returned None')
        rval = False

    inst14 = MI_Instance ()
    inst14.SetValue ('uint64', inst13.GetValue ('uint64'))
    if inst14.GetValue ('uint64').value == inst13.GetValue ('uint64').value:
        inst14.SetValue ('uint64', MI_Uint64 (uint64_1))
        if inst14.GetValue ('uint64').value != uint64_1:
            BookEndPrint ("----- uint64  SetValue failed")
            rval = False
        if inst13.GetValue ('uint64').value == uint64_1:
            BookEndPrint ('----- uint64 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint64 SetValue/GetValue failed')
        rval = False

    # sint64
    sint64_0 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    sint64_1 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    sint64_2 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_1 == sint64_0:
        sint64_1 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_2 == sint64_0 or \
          sint64_2 == sint64_1:
        sint64_2 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)

    sint64_in = MI_Sint64 (sint64_0)
    inst15 = MI_Instance ()
    
    inst15.SetValue ('sint64', sint64_in)
    sint64_out = inst15.GetValue ('sint64')

    if sint64_out is not None:
        if sint64_in.value != sint64_0 or \
               inst15.GetValue ('sint64').value != sint64_0 or \
               sint64_out.value != sint64_0:
            BookEndPrint ('----- sint64 SetValue/GetValue failed')
            rval = False
        else:   
            sint64_in.value = sint64_1
            if sint64_in.value != sint64_1 or \
                   inst15.GetValue ('sint64').value != sint64_0 or \
                   sint64_out.value != sint64_0:
                BookEndPrint ('----- sint64 SetValue/GetValue stored a reference')
                rval = False
            else:
                sint64_out.value = sint64_2
                if sint64_in.value != sint64_1 or \
                       inst15.GetValue ('sint64').value != sint64_0 or \
                       sint64_out.value != sint64_2:
                    BookEndPrint ('----- sint64 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint64 SetValue/GetValue returned None')
        rval = False

    inst16 = MI_Instance ()
    inst16.SetValue ('sint64', inst15.GetValue ('sint64'))
    if inst16.GetValue ('sint64').value == inst15.GetValue ('sint64').value:
        inst16.SetValue ('sint64', MI_Sint64 (sint64_1))
        if inst16.GetValue ('sint64').value != sint64_1:
            BookEndPrint ("----- sint64  SetValue failed")
            rval = False
        if inst15.GetValue ('sint64').value == sint64_1:
            BookEndPrint ('----- sint64 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint64 SetValue/GetValue failed')
        rval = False

    # real32
    real32_0 = ctypes.c_float (random.uniform (-1e37, 1e37))
    real32_1 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_1.value):
        real32_1 = ctypes.c_float (random.uniform (-1e37, 1e37))
    real32_2 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_2.value) or \
              float_eq (real32_1.value, real32_2.value):
        real32_2 = ctypes.c_float (random.uniform (-1e37, 1e37))

    real32_in = MI_Real32 (real32_0.value)
    inst17 = MI_Instance ()
    
    inst17.SetValue ('real32', real32_in)
    real32_out = inst17.GetValue ('real32')

    if real32_out is not None:
        if not float_eq (real32_in.value, real32_0.value) or \
               not float_eq (inst17.GetValue ('real32').value, real32_0.value) or \
               not float_eq (real32_out.value, real32_0.value):
            BookEndPrint ('----- real32 SetValue/GetValue failed')
            rval = False
        else:   
            real32_in.value = real32_1.value
            if not float_eq (real32_in.value, real32_1.value) or \
                   not float_eq (inst17.GetValue ('real32').value, real32_0.value) or \
                   not float_eq (real32_out.value, real32_0.value):
                BookEndPrint ('----- real32 SetValue/GetValue stored a reference')
                rval = False
            else:
                real32_out.value = real32_2.value
                if not float_eq (real32_in.value, real32_1.value) or \
                       not float_eq (inst17.GetValue ('real32').value, real32_0.value) or \
                       not float_eq (real32_out.value, real32_2.value):
                    BookEndPrint ('----- real32 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- real32 SetValue/GetValue returned None')
        rval = False

    inst18 = MI_Instance ()
    inst18.SetValue ('real32', inst17.GetValue ('real32'))
    if float_eq (inst18.GetValue ('real32').value, inst17.GetValue ('real32').value):
        inst18.SetValue ('real32', MI_Real32 (real32_1.value))
        if not float_eq (inst18.GetValue ('real32').value, real32_1.value):
            BookEndPrint ("----- real32  SetValue failed")
            rval = False
        if float_eq (inst17.GetValue ('real32').value, real32_1.value):
            BookEndPrint ('----- real32 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- real32 SetValue/GetValue failed')
        rval = False

    # real64
    real64_0 = random.uniform (-1e307, 1e307)
    real64_1 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_1):
        real64_1 = random.uniform (-1e307, 1e307)
    real64_2 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_2) or \
              float_eq (real64_1, real64_2):
        real64_2 = random.uniform (-1e307, 1e307)

    real64_in = MI_Real64 (real64_0)
    inst19 = MI_Instance ()
    
    inst19.SetValue ('real64', real64_in)
    real64_out = inst19.GetValue ('real64')

    if real64_out is not None:
        if not float_eq (real64_in.value, real64_0) or \
               not float_eq (inst19.GetValue ('real64').value, real64_0) or \
               not float_eq (real64_out.value, real64_0):
            BookEndPrint ('----- real64 SetValue/GetValue failed')
            rval = False
        else:   
            real64_in.value = real64_1
            if not float_eq (real64_in.value, real64_1) or \
                   not float_eq (inst19.GetValue ('real64').value, real64_0) or \
                   not float_eq (real64_out.value, real64_0):
                BookEndPrint ('----- real64 SetValue/GetValue stored a reference')
                rval = False
            else:
                real64_out.value = real64_2
                if not float_eq (real64_in.value, real64_1) or \
                       not float_eq (inst19.GetValue ('real64').value, real64_0) or \
                       not float_eq (real64_out.value, real64_2):
                    BookEndPrint ('----- real64 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- real64 SetValue/GetValue returned None')
        rval = False

    inst20 = MI_Instance ()
    inst20.SetValue ('real64', inst19.GetValue ('real64'))
    if float_eq (inst20.GetValue ('real64').value, inst19.GetValue ('real64').value):
        inst20.SetValue ('real64', MI_Real64 (real64_1))
        if not float_eq (inst20.GetValue ('real64').value, real64_1):
            BookEndPrint ("----- real64  SetValue failed")
            rval = False
        if float_eq (inst19.GetValue ('real64').value, real64_1):
            BookEndPrint ('----- real64 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- real64 SetValue/GetValue failed')
        rval = False

    # char16
    char16_0 = random.randint (0, 0xFFFF)
    char16_1 = random.randint (0, 0xFFFF)
    char16_2 = random.randint (0, 0xFFFF)
    while char16_1 == char16_0:
        char16_1 = random.randint (0, 0xFFFF)
    while char16_2 == char16_0 or \
          char16_2 == char16_1:
        char16_2 = random.randint (0, 0xFFFF)

    char16_in = MI_Char16 (char16_0)
    inst21 = MI_Instance ()
    
    inst21.SetValue ('char16', char16_in)
    char16_out = inst21.GetValue ('char16')

    if char16_out is not None:
        if char16_in.value != char16_0 or \
               inst21.GetValue ('char16').value != char16_0 or \
               char16_out.value != char16_0:
            BookEndPrint ('----- char16 SetValue/GetValue failed')
            rval = False
        else:   
            char16_in.value = char16_1
            if char16_in.value != char16_1 or \
                   inst21.GetValue ('char16').value != char16_0 or \
                   char16_out.value != char16_0:
                BookEndPrint ('----- char16 SetValue/GetValue stored a reference')
                rval = False
            else:
                char16_out.value = char16_2
                if char16_in.value != char16_1 or \
                       inst21.GetValue ('char16').value != char16_0 or \
                       char16_out.value != char16_2:
                    BookEndPrint ('----- char16 SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- char16 SetValue/GetValue returned None')
        rval = False

    inst22 = MI_Instance ()
    inst22.SetValue ('char16', inst21.GetValue ('char16'))
    if inst22.GetValue ('char16').value == inst21.GetValue ('char16').value:
        inst22.SetValue ('char16', MI_Char16 (char16_1))
        if inst22.GetValue ('char16').value != char16_1:
            BookEndPrint ("----- char16  SetValue failed")
            rval = False
        if inst21.GetValue ('char16').value == char16_1:
            BookEndPrint ('----- char16 SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- char16 SetValue/GetValue failed')
        rval = False

    # timestamp
    datetime_0 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))
    datetime_1 = MI_Interval ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49))
    datetime_2 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))

    datetime_in = datetime_0
    inst23 = MI_Instance ()
    
    inst23.SetValue ('datetime', datetime_in)
    datetime_out = inst23.GetValue ('datetime')

    if datetime_out is not None:
        if not datetime_eq (datetime_in, datetime_0) or \
               not datetime_eq (inst23.GetValue ('datetime'), datetime_0) or \
               not datetime_eq (datetime_out, datetime_0):
            BookEndPrint ('----- datetime SetValue/GetValue failed')
            rval = False
        else:   
            datetime_in = datetime_1
            if not datetime_eq (datetime_in, datetime_1) or \
                   not datetime_eq (inst23.GetValue ('datetime'), datetime_0) or \
                   not datetime_eq (datetime_out, datetime_0):
                BookEndPrint ('----- datetime SetValue/GetValue stored a reference')
                rval = False
            else:
                datetime_out = datetime_2
                if not datetime_eq (datetime_in, datetime_1) or \
                       not datetime_eq (inst23.GetValue ('datetime'), datetime_0) or \
                       not datetime_eq (datetime_out, datetime_2):
                    BookEndPrint ('----- datetime SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- datetime SetValue/GetValue returned None')
        rval = False

    inst24 = MI_Instance ()
    inst24.SetValue ('datetime', inst23.GetValue ('datetime'))
    if datetime_eq (inst24.GetValue ('datetime'), inst23.GetValue ('datetime')):
        inst24.SetValue ('datetime', datetime_1)
        if not datetime_eq (inst24.GetValue ('datetime'), datetime_1):
            BookEndPrint ("----- datetime  SetValue failed")
            rval = False
        if datetime_eq (inst23.GetValue ('datetime'), datetime_1):
            BookEndPrint ('----- datetime SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- datetime SetValue/GetValue failed')
        rval = False

    # string
    string_vals = [
        'apple', 'banana', 'peach', 'pear', 'orange',
        'watermelon', 'lemon', 'grapefruit', 'kiwi', 'plum',
        'chicken', 'dog', 'cat', 'goat', 'sheep',
        'rabbit', 'cow', 'horse', 'llama', 'pig'
        ]
    string_0 = random.randint (0, len (string_vals) - 1)
    string_1 = random.randint (0, len (string_vals) -1)
    while string_0 == string_1:
        string_1 = random.randint (0, len (string_vals) -1)
    string_2 = random.randint (0, len (string_vals) -1)
    while string_0 == string_2 or string_1 == string_2:
        string_2 = random.randint (0, len (string_vals) -1)

    string_0 = string_vals[string_0]
    string_1 = string_vals[string_1]
    string_2 = string_vals[string_2]

    uint8_0 = random.randint (0, 0xFF)
    uint8_1 = random.randint (0, 0xFF)
    uint8_2 = random.randint (0, 0xFF)
    while uint8_1 == uint8_0:
        uint8_1 = random.randint (0, 0xFF)
    while uint8_2 == uint8_0 or \
          uint8_2 == uint8_1:
        uint8_2 = random.randint (0, 0xFF)

    string_in = MI_String (string_0)
    inst25 = MI_Instance ()
    
    inst25.SetValue ('string', string_in)
    string_out = inst25.GetValue ('string')

    if string_out is not None:
        if string_in.value != string_0 or \
               inst25.GetValue ('string').value != string_0 or \
               string_out.value != string_0:
            BookEndPrint ('----- string SetValue/GetValue failed')
            rval = False
        else:   
            string_in.value = string_1
            if string_in.value != string_1 or \
                   inst25.GetValue ('string').value != string_0 or \
                   string_out.value != string_0:
                BookEndPrint ('----- string SetValue/GetValue stored a reference')
                rval = False
            else:
                string_out.value = string_2
                if string_in.value != string_1 or \
                       inst25.GetValue ('string').value != string_0 or \
                       string_out.value != string_2:
                    BookEndPrint ('----- string SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- string SetValue/GetValue returned None')
        rval = False

    inst26 = MI_Instance ()
    inst26.SetValue ('string', inst25.GetValue ('string'))
    if inst26.GetValue ('string').value == inst25.GetValue ('string').value:
        inst26.SetValue ('string', MI_String (string_1))
        if inst26.GetValue ('string').value != string_1:
            BookEndPrint ("----- string  SetValue failed")
            rval = False
        if inst25.GetValue ('string').value == string_1:
            BookEndPrint ('----- string SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- string SetValue/GetValue failed')
        rval = False

    # uint8a
    uint8_3 = random.randint (0, 0xFF)
    while uint8_0 == uint8_3 or \
          uint8_1 == uint8_3 or \
          uint8_2 == uint8_3:
        uint8_3 = random.randint (0, 0xFF)
    uint8_4 = random.randint (0, 0xFF)
    while uint8_0 == uint8_4 or \
          uint8_1 == uint8_4 or \
          uint8_2 == uint8_4 or \
          uint8_3 == uint8_4:
        uint8_4 = random.randint (0, 0xFF)
    uint8_5 = random.randint (0, 0xFF)
    while uint8_0 == uint8_5 or \
          uint8_1 == uint8_5 or \
          uint8_2 == uint8_5 or \
          uint8_3 == uint8_5 or \
          uint8_4 == uint8_5:
        uint8_5 = random.randint (0, 0xFF)
    uint8_6 = random.randint (0, 0xFF)
    while uint8_0 == uint8_6 or \
          uint8_1 == uint8_6 or \
          uint8_2 == uint8_6 or \
          uint8_3 == uint8_6 or \
          uint8_4 == uint8_6 or \
          uint8_5 == uint8_6:
        uint8_6 = random.randint (0, 0xFF)
    uint8_7 = random.randint (0, 0xFF)
    while uint8_0 == uint8_7 or \
          uint8_1 == uint8_7 or \
          uint8_2 == uint8_7 or \
          uint8_3 == uint8_7 or \
          uint8_4 == uint8_7 or \
          uint8_5 == uint8_7 or \
          uint8_6 == uint8_7:
        uint8_7 = random.randint (0, 0xFF)
    uint8_8 = random.randint (0, 0xFF)
    while uint8_0 == uint8_8 or \
          uint8_1 == uint8_8 or \
          uint8_2 == uint8_8 or \
          uint8_3 == uint8_8 or \
          uint8_4 == uint8_8 or \
          uint8_5 == uint8_8 or \
          uint8_6 == uint8_8 or \
          uint8_7 == uint8_8:
        uint8_8 = random.randint (0, 0xFF)

    uint8a_0 = MI_Uint8A ((uint8_0, uint8_1, uint8_2))
    uint8a_1 = MI_Uint8A ((uint8_3, uint8_4, uint8_5))
    uint8a_2 = MI_Uint8A ((uint8_6, uint8_7, uint8_8))

    uint8a_in = uint8a_0
    inst27 = MI_Instance ()
    
    inst27.SetValue ('uint8a', uint8a_in)
    uint8a_out = inst27.GetValue ('uint8a')

    if uint8a_out is not None:
        if not array_eq (uint8a_in, uint8a_0) or \
               not array_eq (inst27.GetValue ('uint8a'),uint8a_0) or \
               not array_eq (uint8a_out, uint8a_0):
            BookEndPrint ('----- uint8a SetValue/GetValue failed')
            rval = False
        else:   
            uint8a_in = uint8a_1
            if not array_eq (uint8a_in, uint8a_1) or \
                   not array_eq (inst27.GetValue ('uint8a'), uint8a_0) or \
                   not array_eq (uint8a_out, uint8a_0):
                BookEndPrint ('----- uint8a SetValue/GetValue stored a reference')
                rval = False
            else:
                uint8a_out = uint8a_2
                if not array_eq (uint8a_in, uint8a_1) or \
                       not array_eq (inst27.GetValue ('uint8a'), uint8a_0) or \
                       not array_eq (uint8a_out, uint8a_2):
                    BookEndPrint ('----- uint8a SetValue/GetValue stored a reference')
                    rval = False
                else:
                    uint8a_out = inst27.GetValue ('uint8a')
                    uint8a_out.setValueAt (0, uint8_2)
                    if array_eq (uint8a_out, inst27.GetValue ('uint8a')) or \
                       array_eq (uint8a_out, uint8a_2):
                        BookEndPrint ('----- uint8a SetValue/GetValue stored a reference')
                        rval = False
    else:
        BookEndPrint ('----- uint8a SetValue/GetValue returned None')
        rval = False

    inst28 = MI_Instance ()
    inst28.SetValue ('uint8a', inst27.GetValue ('uint8a'))
    if array_eq (inst28.GetValue ('uint8a'), inst27.GetValue ('uint8a')):
        inst28.SetValue ('uint8a', uint8a_1)
        if not array_eq (inst28.GetValue ('uint8a'), uint8a_1):
            BookEndPrint ("----- uint8a  SetValue failed")
            rval = False
        if array_eq (inst27.GetValue ('uint8a'), uint8a_1):
            BookEndPrint ('----- uint8a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint8a SetValue/GetValue failed')
        rval = False

    # sint8a
    sint8_3 = random.randint (-0x80, 0x7F)
    while sint8_0 == sint8_3 or \
          sint8_1 == sint8_3 or \
          sint8_2 == sint8_3:
        sint8_3 = random.randint (-0x80, 0x7F)
    sint8_4 = random.randint (-0x80, 0x7F)
    while sint8_0 == sint8_4 or \
          sint8_1 == sint8_4 or \
          sint8_2 == sint8_4 or \
          sint8_3 == sint8_4:
        sint8_4 = random.randint (-0x80, 0x7F)
    sint8_5 = random.randint (-0x80, 0x7F)
    while sint8_0 == sint8_5 or \
          sint8_1 == sint8_5 or \
          sint8_2 == sint8_5 or \
          sint8_3 == sint8_5 or \
          sint8_4 == sint8_5:
        sint8_5 = random.randint (-0x80, 0x7F)
    sint8_6 = random.randint (-0x80, 0x7F)
    while sint8_0 == sint8_6 or \
          sint8_1 == sint8_6 or \
          sint8_2 == sint8_6 or \
          sint8_3 == sint8_6 or \
          sint8_4 == sint8_6 or \
          sint8_5 == sint8_6:
        sint8_6 = random.randint (-0x80, 0x7F)
    sint8_7 = random.randint (-0x80, 0x7F)
    while sint8_0 == sint8_7 or \
          sint8_1 == sint8_7 or \
          sint8_2 == sint8_7 or \
          sint8_3 == sint8_7 or \
          sint8_4 == sint8_7 or \
          sint8_5 == sint8_7 or \
          sint8_6 == sint8_7:
        sint8_7 = random.randint (-0x80, 0x7F)
    sint8_8 = random.randint (-0x80, 0x7F)
    while sint8_0 == sint8_8 or \
          sint8_1 == sint8_8 or \
          sint8_2 == sint8_8 or \
          sint8_3 == sint8_8 or \
          sint8_4 == sint8_8 or \
          sint8_5 == sint8_8 or \
          sint8_6 == sint8_8 or \
          sint8_7 == sint8_8:
        sint8_8 = random.randint (-0x80, 0x7F)

    sint8a_0 = MI_Sint8A ((sint8_0, sint8_1, sint8_2))
    sint8a_1 = MI_Sint8A ((sint8_3, sint8_4, sint8_5))
    sint8a_2 = MI_Sint8A ((sint8_6, sint8_7, sint8_8))

    sint8a_in = sint8a_0
    inst29 = MI_Instance ()
    
    inst29.SetValue ('sint8a', sint8a_in)
    sint8a_out = inst29.GetValue ('sint8a')

    if sint8a_out is not None:
        if not array_eq (sint8a_in, sint8a_0) or \
               not array_eq (inst29.GetValue ('sint8a'),sint8a_0) or \
               not array_eq (sint8a_out, sint8a_0):
            BookEndPrint ('----- sint8a SetValue/GetValue failed')
            rval = False
        else:   
            sint8a_in = sint8a_1
            if not array_eq (sint8a_in, sint8a_1) or \
                   not array_eq (inst29.GetValue ('sint8a'), sint8a_0) or \
                   not array_eq (sint8a_out, sint8a_0):
                BookEndPrint ('----- sint8a SetValue/GetValue stored a reference')
                rval = False
            else:
                sint8a_out = sint8a_2
                if not array_eq (sint8a_in, sint8a_1) or \
                       not array_eq (inst29.GetValue ('sint8a'), sint8a_0) or \
                       not array_eq (sint8a_out, sint8a_2):
                    BookEndPrint ('----- sint8a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint8a SetValue/GetValue returned None')
        rval = False

    inst30 = MI_Instance ()
    inst30.SetValue ('sint8a', inst29.GetValue ('sint8a'))
    if array_eq (inst30.GetValue ('sint8a'), inst29.GetValue ('sint8a')):
        inst30.SetValue ('sint8a', sint8a_1)
        if not array_eq (inst30.GetValue ('sint8a'), sint8a_1):
            BookEndPrint ("----- sint8a  SetValue failed")
            rval = False
        if array_eq (inst29.GetValue ('sint8a'), sint8a_1):
            BookEndPrint ('----- sint8a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint8a SetValue/GetValue failed')
        rval = False

    # uint16a
    uint16_3 = random.randint (0, 0xFFFF)
    while uint16_0 == uint16_3 or \
          uint16_1 == uint16_3 or \
          uint16_2 == uint16_3:
        uint16_3 = random.randint (0, 0xFFFF)
    uint16_4 = random.randint (0, 0xFFFF)
    while uint16_0 == uint16_4 or \
          uint16_1 == uint16_4 or \
          uint16_2 == uint16_4 or \
          uint16_3 == uint16_4:
        uint16_4 = random.randint (0, 0xFFFF)
    uint16_5 = random.randint (0, 0xFFFF)
    while uint16_0 == uint16_5 or \
          uint16_1 == uint16_5 or \
          uint16_2 == uint16_5 or \
          uint16_3 == uint16_5 or \
          uint16_4 == uint16_5:
        uint16_5 = random.randint (0, 0xFFFF)
    uint16_6 = random.randint (0, 0xFFFF)
    while uint16_0 == uint16_6 or \
          uint16_1 == uint16_6 or \
          uint16_2 == uint16_6 or \
          uint16_3 == uint16_6 or \
          uint16_4 == uint16_6 or \
          uint16_5 == uint16_6:
        uint16_6 = random.randint (0, 0xFFFF)
    uint16_7 = random.randint (0, 0xFFFF)
    while uint16_0 == uint16_7 or \
          uint16_1 == uint16_7 or \
          uint16_2 == uint16_7 or \
          uint16_3 == uint16_7 or \
          uint16_4 == uint16_7 or \
          uint16_5 == uint16_7 or \
          uint16_6 == uint16_7:
        uint16_7 = random.randint (0, 0xFFFF)
    uint16_8 = random.randint (0, 0xFFFF)
    while uint16_0 == uint16_8 or \
          uint16_1 == uint16_8 or \
          uint16_2 == uint16_8 or \
          uint16_3 == uint16_8 or \
          uint16_4 == uint16_8 or \
          uint16_5 == uint16_8 or \
          uint16_6 == uint16_8 or \
          uint16_7 == uint16_8:
        uint16_8 = random.randint (0, 0xFFFF)

    uint16a_0 = MI_Uint16A ((uint16_0, uint16_1, uint16_2))
    uint16a_1 = MI_Uint16A ((uint16_3, uint16_4, uint16_5))
    uint16a_2 = MI_Uint16A ((uint16_6, uint16_7, uint16_8))

    uint16a_in = uint16a_0
    inst31 = MI_Instance ()
    
    inst31.SetValue ('uint16a', uint16a_in)
    uint16a_out = inst31.GetValue ('uint16a')

    if uint16a_out is not None:
        if not array_eq (uint16a_in, uint16a_0) or \
               not array_eq (inst31.GetValue ('uint16a'),uint16a_0) or \
               not array_eq (uint16a_out, uint16a_0):
            BookEndPrint ('----- uint16a SetValue/GetValue failed')
            rval = False
        else:   
            uint16a_in = uint16a_1
            if not array_eq (uint16a_in, uint16a_1) or \
                   not array_eq (inst31.GetValue ('uint16a'), uint16a_0) or \
                   not array_eq (uint16a_out, uint16a_0):
                BookEndPrint ('----- uint16a SetValue/GetValue stored a reference')
                rval = False
            else:
                uint16a_out = uint16a_2
                if not array_eq (uint16a_in, uint16a_1) or \
                       not array_eq (inst31.GetValue ('uint16a'), uint16a_0) or \
                       not array_eq (uint16a_out, uint16a_2):
                    BookEndPrint ('----- uint16a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint16a SetValue/GetValue returned None')
        rval = False

    inst32 = MI_Instance ()
    inst32.SetValue ('uint16a', inst31.GetValue ('uint16a'))
    if array_eq (inst32.GetValue ('uint16a'), inst31.GetValue ('uint16a')):
        inst32.SetValue ('uint16a', uint16a_1)
        if not array_eq (inst32.GetValue ('uint16a'), uint16a_1):
            BookEndPrint ("----- uint16a  SetValue failed")
            rval = False
        if array_eq (inst31.GetValue ('uint16a'), uint16a_1):
            BookEndPrint ('----- uint16a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint16a SetValue/GetValue failed')
        rval = False


    # sint16a
    sint16_3 = random.randint (-0x8000, 0x7FFF)
    while sint16_0 == sint16_3 or \
          sint16_1 == sint16_3 or \
          sint16_2 == sint16_3:
        sint16_3 = random.randint (-0x8000, 0x7FFF)
    sint16_4 = random.randint (-0x8000, 0x7FFF)
    while sint16_0 == sint16_4 or \
          sint16_1 == sint16_4 or \
          sint16_2 == sint16_4 or \
          sint16_3 == sint16_4:
        sint16_4 = random.randint (-0x8000, 0x7FFF)
    sint16_5 = random.randint (-0x8000, 0x7FFF)
    while sint16_0 == sint16_5 or \
          sint16_1 == sint16_5 or \
          sint16_2 == sint16_5 or \
          sint16_3 == sint16_5 or \
          sint16_4 == sint16_5:
        sint16_5 = random.randint (-0x8000, 0x7FFF)
    sint16_6 = random.randint (-0x8000, 0x7FFF)
    while sint16_0 == sint16_6 or \
          sint16_1 == sint16_6 or \
          sint16_2 == sint16_6 or \
          sint16_3 == sint16_6 or \
          sint16_4 == sint16_6 or \
          sint16_5 == sint16_6:
        sint16_6 = random.randint (-0x8000, 0x7FFF)
    sint16_7 = random.randint (-0x8000, 0x7FFF)
    while sint16_0 == sint16_7 or \
          sint16_1 == sint16_7 or \
          sint16_2 == sint16_7 or \
          sint16_3 == sint16_7 or \
          sint16_4 == sint16_7 or \
          sint16_5 == sint16_7 or \
          sint16_6 == sint16_7:
        sint16_7 = random.randint (-0x8000, 0x7FFF)
    sint16_8 = random.randint (-0x8000, 0x7FFF)
    while sint16_0 == sint16_8 or \
          sint16_1 == sint16_8 or \
          sint16_2 == sint16_8 or \
          sint16_3 == sint16_8 or \
          sint16_4 == sint16_8 or \
          sint16_5 == sint16_8 or \
          sint16_6 == sint16_8 or \
          sint16_7 == sint16_8:
        sint16_8 = random.randint (-0x8000, 0x7FFF)

    sint16a_0 = MI_Sint16A ((sint16_0, sint16_1, sint16_2))
    sint16a_1 = MI_Sint16A ((sint16_3, sint16_4, sint16_5))
    sint16a_2 = MI_Sint16A ((sint16_6, sint16_7, sint16_8))

    sint16a_in = sint16a_0
    inst33 = MI_Instance ()
    
    inst33.SetValue ('sint16a', sint16a_in)
    sint16a_out = inst33.GetValue ('sint16a')

    if sint16a_out is not None:
        if not array_eq (sint16a_in, sint16a_0) or \
               not array_eq (inst33.GetValue ('sint16a'),sint16a_0) or \
               not array_eq (sint16a_out, sint16a_0):
            BookEndPrint ('----- sint16a SetValue/GetValue failed')
            rval = False
        else:   
            sint16a_in = sint16a_1
            if not array_eq (sint16a_in, sint16a_1) or \
                   not array_eq (inst33.GetValue ('sint16a'), sint16a_0) or \
                   not array_eq (sint16a_out, sint16a_0):
                BookEndPrint ('----- sint16a SetValue/GetValue stored a reference')
                rval = False
            else:
                sint16a_out = sint16a_2
                if not array_eq (sint16a_in, sint16a_1) or \
                       not array_eq (inst33.GetValue ('sint16a'), sint16a_0) or \
                       not array_eq (sint16a_out, sint16a_2):
                    BookEndPrint ('----- sint16a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint16a SetValue/GetValue returned None')
        rval = False

    inst34 = MI_Instance ()
    inst34.SetValue ('sint16a', inst33.GetValue ('sint16a'))
    if array_eq (inst34.GetValue ('sint16a'), inst33.GetValue ('sint16a')):
        inst34.SetValue ('sint16a', sint16a_1)
        if not array_eq (inst34.GetValue ('sint16a'), sint16a_1):
            BookEndPrint ("----- sint16a  SetValue failed")
            rval = False
        if array_eq (inst33.GetValue ('sint16a'), sint16a_1):
            BookEndPrint ('----- sint16a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint16a SetValue/GetValue failed')
        rval = False

    # uint32a
    uint32_3 = random.randint (0, 0xFFFFFFFF)
    while uint32_0 == uint32_3 or \
          uint32_1 == uint32_3 or \
          uint32_2 == uint32_3:
        uint32_3 = random.randint (0, 0xFFFFFFFF)
    uint32_4 = random.randint (0, 0xFFFFFFFF)
    while uint32_0 == uint32_4 or \
          uint32_1 == uint32_4 or \
          uint32_2 == uint32_4 or \
          uint32_3 == uint32_4:
        uint32_4 = random.randint (0, 0xFFFFFFFF)
    uint32_5 = random.randint (0, 0xFFFFFFFF)
    while uint32_0 == uint32_5 or \
          uint32_1 == uint32_5 or \
          uint32_2 == uint32_5 or \
          uint32_3 == uint32_5 or \
          uint32_4 == uint32_5:
        uint32_5 = random.randint (0, 0xFFFFFFFF)
    uint32_6 = random.randint (0, 0xFFFFFFFF)
    while uint32_0 == uint32_6 or \
          uint32_1 == uint32_6 or \
          uint32_2 == uint32_6 or \
          uint32_3 == uint32_6 or \
          uint32_4 == uint32_6 or \
          uint32_5 == uint32_6:
        uint32_6 = random.randint (0, 0xFFFFFFFF)
    uint32_7 = random.randint (0, 0xFFFFFFFF)
    while uint32_0 == uint32_7 or \
          uint32_1 == uint32_7 or \
          uint32_2 == uint32_7 or \
          uint32_3 == uint32_7 or \
          uint32_4 == uint32_7 or \
          uint32_5 == uint32_7 or \
          uint32_6 == uint32_7:
        uint32_7 = random.randint (0, 0xFFFFFFFF)
    uint32_8 = random.randint (0, 0xFFFFFFFF)
    while uint32_0 == uint32_8 or \
          uint32_1 == uint32_8 or \
          uint32_2 == uint32_8 or \
          uint32_3 == uint32_8 or \
          uint32_4 == uint32_8 or \
          uint32_5 == uint32_8 or \
          uint32_6 == uint32_8 or \
          uint32_7 == uint32_8:
        uint32_8 = random.randint (0, 0xFFFFFFFF)

    uint32a_0 = MI_Uint32A ((uint32_0, uint32_1, uint32_2))
    uint32a_1 = MI_Uint32A ((uint32_3, uint32_4, uint32_5))
    uint32a_2 = MI_Uint32A ((uint32_6, uint32_7, uint32_8))

    uint32a_in = uint32a_0
    inst35 = MI_Instance ()
    
    inst35.SetValue ('uint32a', uint32a_in)
    uint32a_out = inst35.GetValue ('uint32a')

    if uint32a_out is not None:
        if not array_eq (uint32a_in, uint32a_0) or \
               not array_eq (inst35.GetValue ('uint32a'),uint32a_0) or \
               not array_eq (uint32a_out, uint32a_0):
            BookEndPrint ('----- uint32a SetValue/GetValue failed')
            rval = False
        else:   
            uint32a_in = uint32a_1
            if not array_eq (uint32a_in, uint32a_1) or \
                   not array_eq (inst35.GetValue ('uint32a'), uint32a_0) or \
                   not array_eq (uint32a_out, uint32a_0):
                BookEndPrint ('----- uint32a SetValue/GetValue stored a reference')
                rval = False
            else:
                uint32a_out = uint32a_2
                if not array_eq (uint32a_in, uint32a_1) or \
                       not array_eq (inst35.GetValue ('uint32a'), uint32a_0) or \
                       not array_eq (uint32a_out, uint32a_2):
                    BookEndPrint ('----- uint32a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint32a SetValue/GetValue returned None')
        rval = False

    inst36 = MI_Instance ()
    inst36.SetValue ('uint32a', inst35.GetValue ('uint32a'))
    if array_eq (inst36.GetValue ('uint32a'), inst35.GetValue ('uint32a')):
        inst36.SetValue ('uint32a', uint32a_1)
        if not array_eq (inst36.GetValue ('uint32a'), uint32a_1):
            BookEndPrint ("----- uint32a  SetValue failed")
            rval = False
        if array_eq (inst35.GetValue ('uint32a'), uint32a_1):
            BookEndPrint ('----- uint32a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint32a SetValue/GetValue failed')
        rval = False

    # sint32a
    sint32_3 = random.randint (-0x80000000, 0x7FFFFFFF)
    while sint32_0 == sint32_3 or \
          sint32_1 == sint32_3 or \
          sint32_2 == sint32_3:
        sint32_3 = random.randint (-0x80000000, 0x7FFFFFFF)
    sint32_4 = random.randint (-0x80000000, 0x7FFFFFFF)
    while sint32_0 == sint32_4 or \
          sint32_1 == sint32_4 or \
          sint32_2 == sint32_4 or \
          sint32_3 == sint32_4:
        sint32_4 = random.randint (-0x80000000, 0x7FFFFFFF)
    sint32_5 = random.randint (-0x80000000, 0x7FFFFFFF)
    while sint32_0 == sint32_5 or \
          sint32_1 == sint32_5 or \
          sint32_2 == sint32_5 or \
          sint32_3 == sint32_5 or \
          sint32_4 == sint32_5:
        sint32_5 = random.randint (-0x80000000, 0x7FFFFFFF)
    sint32_6 = random.randint (-0x80000000, 0x7FFFFFFF)
    while sint32_0 == sint32_6 or \
          sint32_1 == sint32_6 or \
          sint32_2 == sint32_6 or \
          sint32_3 == sint32_6 or \
          sint32_4 == sint32_6 or \
          sint32_5 == sint32_6:
        sint32_6 = random.randint (-0x80000000, 0x7FFFFFFF)
    sint32_7 = random.randint (-0x80000000, 0x7FFFFFFF)
    while sint32_0 == sint32_7 or \
          sint32_1 == sint32_7 or \
          sint32_2 == sint32_7 or \
          sint32_3 == sint32_7 or \
          sint32_4 == sint32_7 or \
          sint32_5 == sint32_7 or \
          sint32_6 == sint32_7:
        sint32_7 = random.randint (-0x80000000, 0x7FFFFFFF)
    sint32_8 = random.randint (-0x80000000, 0x7FFFFFFF)
    while sint32_0 == sint32_8 or \
          sint32_1 == sint32_8 or \
          sint32_2 == sint32_8 or \
          sint32_3 == sint32_8 or \
          sint32_4 == sint32_8 or \
          sint32_5 == sint32_8 or \
          sint32_6 == sint32_8 or \
          sint32_7 == sint32_8:
        sint32_8 = random.randint (-0x80000000, 0x7FFFFFFF)

    sint32a_0 = MI_Sint32A ((sint32_0, sint32_1, sint32_2))
    sint32a_1 = MI_Sint32A ((sint32_3, sint32_4, sint32_5))
    sint32a_2 = MI_Sint32A ((sint32_6, sint32_7, sint32_8))

    sint32a_in = sint32a_0
    inst37 = MI_Instance ()
    
    inst37.SetValue ('sint32a', sint32a_in)
    sint32a_out = inst37.GetValue ('sint32a')

    if sint32a_out is not None:
        if not array_eq (sint32a_in, sint32a_0) or \
               not array_eq (inst37.GetValue ('sint32a'),sint32a_0) or \
               not array_eq (sint32a_out, sint32a_0):
            BookEndPrint ('----- sint32a SetValue/GetValue failed')
            rval = False
        else:   
            sint32a_in = sint32a_1
            if not array_eq (sint32a_in, sint32a_1) or \
                   not array_eq (inst37.GetValue ('sint32a'), sint32a_0) or \
                   not array_eq (sint32a_out, sint32a_0):
                BookEndPrint ('----- sint32a SetValue/GetValue stored a reference')
                rval = False
            else:
                sint32a_out = sint32a_2
                if not array_eq (sint32a_in, sint32a_1) or \
                       not array_eq (inst37.GetValue ('sint32a'), sint32a_0) or \
                       not array_eq (sint32a_out, sint32a_2):
                    BookEndPrint ('----- sint32a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint32a SetValue/GetValue returned None')
        rval = False

    inst38 = MI_Instance ()
    inst38.SetValue ('sint32a', inst37.GetValue ('sint32a'))
    if array_eq (inst38.GetValue ('sint32a'), inst37.GetValue ('sint32a')):
        inst38.SetValue ('sint32a', sint32a_1)
        if not array_eq (inst38.GetValue ('sint32a'), sint32a_1):
            BookEndPrint ("----- sint32a  SetValue failed")
            rval = False
        if array_eq (inst37.GetValue ('sint32a'), sint32a_1):
            BookEndPrint ('----- sint32a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint32a SetValue/GetValue failed')
        rval = False

    # uint64a
    uint64_3 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_0 == uint64_3 or \
          uint64_1 == uint64_3 or \
          uint64_2 == uint64_3:
        uint64_3 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    uint64_4 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_0 == uint64_4 or \
          uint64_1 == uint64_4 or \
          uint64_2 == uint64_4 or \
          uint64_3 == uint64_4:
        uint64_4 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    uint64_5 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_0 == uint64_5 or \
          uint64_1 == uint64_5 or \
          uint64_2 == uint64_5 or \
          uint64_3 == uint64_5 or \
          uint64_4 == uint64_5:
        uint64_5 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    uint64_6 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_0 == uint64_6 or \
          uint64_1 == uint64_6 or \
          uint64_2 == uint64_6 or \
          uint64_3 == uint64_6 or \
          uint64_4 == uint64_6 or \
          uint64_5 == uint64_6:
        uint64_6 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    uint64_7 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_0 == uint64_7 or \
          uint64_1 == uint64_7 or \
          uint64_2 == uint64_7 or \
          uint64_3 == uint64_7 or \
          uint64_4 == uint64_7 or \
          uint64_5 == uint64_7 or \
          uint64_6 == uint64_7:
        uint64_7 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    uint64_8 = random.randint (0, 0xFFFFFFFFFFFFFFFF)
    while uint64_0 == uint64_8 or \
          uint64_1 == uint64_8 or \
          uint64_2 == uint64_8 or \
          uint64_3 == uint64_8 or \
          uint64_4 == uint64_8 or \
          uint64_5 == uint64_8 or \
          uint64_6 == uint64_8 or \
          uint64_7 == uint64_8:
        uint64_8 = random.randint (0, 0xFFFFFFFFFFFFFFFF)

    uint64a_0 = MI_Uint64A ((uint64_0, uint64_1, uint64_2))
    uint64a_1 = MI_Uint64A ((uint64_3, uint64_4, uint64_5))
    uint64a_2 = MI_Uint64A ((uint64_6, uint64_7, uint64_8))

    uint64a_in = uint64a_0
    inst39 = MI_Instance ()
    
    inst39.SetValue ('uint64a', uint64a_in)
    uint64a_out = inst39.GetValue ('uint64a')

    if uint64a_out is not None:
        if not array_eq (uint64a_in, uint64a_0) or \
               not array_eq (inst39.GetValue ('uint64a'),uint64a_0) or \
               not array_eq (uint64a_out, uint64a_0):
            BookEndPrint ('----- uint64a SetValue/GetValue failed')
            rval = False
        else:   
            uint64a_in = uint64a_1
            if not array_eq (uint64a_in, uint64a_1) or \
                   not array_eq (inst39.GetValue ('uint64a'), uint64a_0) or \
                   not array_eq (uint64a_out, uint64a_0):
                BookEndPrint ('----- uint64a SetValue/GetValue stored a reference')
                rval = False
            else:
                uint64a_out = uint64a_2
                if not array_eq (uint64a_in, uint64a_1) or \
                       not array_eq (inst39.GetValue ('uint64a'), uint64a_0) or \
                       not array_eq (uint64a_out, uint64a_2):
                    BookEndPrint ('----- uint64a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint64a SetValue/GetValue returned None')
        rval = False

    inst40 = MI_Instance ()
    inst40.SetValue ('uint64a', inst39.GetValue ('uint64a'))
    if array_eq (inst40.GetValue ('uint64a'), inst39.GetValue ('uint64a')):
        inst40.SetValue ('uint64a', uint64a_1)
        if not array_eq (inst40.GetValue ('uint64a'), uint64a_1):
            BookEndPrint ("----- uint64a  SetValue failed")
            rval = False
        if array_eq (inst39.GetValue ('uint64a'), uint64a_1):
            BookEndPrint ('----- uint64a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint64a SetValue/GetValue failed')
        rval = False

    # sint64a
    sint64_3 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_0 == sint64_3 or \
          sint64_1 == sint64_3 or \
          sint64_2 == sint64_3:
        sint64_3 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    sint64_4 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_0 == sint64_4 or \
          sint64_1 == sint64_4 or \
          sint64_2 == sint64_4 or \
          sint64_3 == sint64_4:
        sint64_4 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    sint64_5 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_0 == sint64_5 or \
          sint64_1 == sint64_5 or \
          sint64_2 == sint64_5 or \
          sint64_3 == sint64_5 or \
          sint64_4 == sint64_5:
        sint64_5 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    sint64_6 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_0 == sint64_6 or \
          sint64_1 == sint64_6 or \
          sint64_2 == sint64_6 or \
          sint64_3 == sint64_6 or \
          sint64_4 == sint64_6 or \
          sint64_5 == sint64_6:
        sint64_6 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    sint64_7 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_0 == sint64_7 or \
          sint64_1 == sint64_7 or \
          sint64_2 == sint64_7 or \
          sint64_3 == sint64_7 or \
          sint64_4 == sint64_7 or \
          sint64_5 == sint64_7 or \
          sint64_6 == sint64_7:
        sint64_7 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    sint64_8 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
    while sint64_0 == sint64_8 or \
          sint64_1 == sint64_8 or \
          sint64_2 == sint64_8 or \
          sint64_3 == sint64_8 or \
          sint64_4 == sint64_8 or \
          sint64_5 == sint64_8 or \
          sint64_6 == sint64_8 or \
          sint64_7 == sint64_8:
        sint64_8 = random.randint (-0x8000000000000000, 0x7FFFFFFFFFFFFFFF)

    sint64a_0 = MI_Sint64A ((sint64_0, sint64_1, sint64_2))
    sint64a_1 = MI_Sint64A ((sint64_3, sint64_4, sint64_5))
    sint64a_2 = MI_Sint64A ((sint64_6, sint64_7, sint64_8))

    sint64a_in = sint64a_0
    inst41 = MI_Instance ()
    
    inst41.SetValue ('sint64a', sint64a_in)
    sint64a_out = inst41.GetValue ('sint64a')

    if sint64a_out is not None:
        if not array_eq (sint64a_in, sint64a_0) or \
               not array_eq (inst41.GetValue ('sint64a'),sint64a_0) or \
               not array_eq (sint64a_out, sint64a_0):
            BookEndPrint ('----- sint64a SetValue/GetValue failed')
            rval = False
        else:   
            sint64a_in = sint64a_1
            if not array_eq (sint64a_in, sint64a_1) or \
                   not array_eq (inst41.GetValue ('sint64a'), sint64a_0) or \
                   not array_eq (sint64a_out, sint64a_0):
                BookEndPrint ('----- sint64a SetValue/GetValue stored a reference')
                rval = False
            else:
                sint64a_out = sint64a_2
                if not array_eq (sint64a_in, sint64a_1) or \
                       not array_eq (inst41.GetValue ('sint64a'), sint64a_0) or \
                       not array_eq (sint64a_out, sint64a_2):
                    BookEndPrint ('----- sint64a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- sint64a SetValue/GetValue returned None')
        rval = False

    inst42 = MI_Instance ()
    inst42.SetValue ('sint64a', inst41.GetValue ('sint64a'))
    if array_eq (inst42.GetValue ('sint64a'), inst41.GetValue ('sint64a')):
        inst42.SetValue ('sint64a', sint64a_1)
        if not array_eq (inst42.GetValue ('sint64a'), sint64a_1):
            BookEndPrint ("----- sint64a  SetValue failed")
            rval = False
        if array_eq (inst41.GetValue ('sint64a'), sint64a_1):
            BookEndPrint ('----- sint64a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- sint64a SetValue/GetValue failed')
        rval = False

    # real32a
    real32_3 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_3.value) or \
          float_eq (real32_1.value, real32_3.value) or \
          float_eq (real32_2.value, real32_3.value):
        real32_3 = ctypes.c_float (random.uniform (-1e37, 1e37))
    real32_4 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_4.value) or \
          float_eq (real32_1.value, real32_4.value) or \
          float_eq (real32_2.value, real32_4.value) or \
          float_eq (real32_3.value, real32_4.value):
        real32_4 = ctypes.c_float (random.uniform (-1e37, 1e37))
    real32_5 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_5.value) or \
          float_eq (real32_1.value, real32_5.value) or \
          float_eq (real32_2.value, real32_5.value) or \
          float_eq (real32_3.value, real32_5.value) or \
          float_eq (real32_4.value, real32_5.value):
        real32_5 = ctypes.c_float (random.uniform (-1e37, 1e37))
    real32_6 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_6.value) or \
          float_eq (real32_1.value, real32_6.value) or \
          float_eq (real32_2.value, real32_6.value) or \
          float_eq (real32_3.value, real32_6.value) or \
          float_eq (real32_4.value, real32_6.value) or \
          float_eq (real32_5.value, real32_6.value):
        real32_6 = ctypes.c_float (random.uniform (-1e37, 1e37))
    real32_7 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_7.value) or \
          float_eq (real32_1.value, real32_7.value) or \
          float_eq (real32_2.value, real32_7.value) or \
          float_eq (real32_3.value, real32_7.value) or \
          float_eq (real32_4.value, real32_7.value) or \
          float_eq (real32_5.value, real32_7.value) or \
          float_eq (real32_6.value, real32_7.value):
        real32_7 = ctypes.c_float (random.uniform (-1e37, 1e37))
    real32_8 = ctypes.c_float (random.uniform (-1e37, 1e37))
    while float_eq (real32_0.value, real32_8.value) or \
          float_eq (real32_1.value, real32_8.value) or \
          float_eq (real32_2.value, real32_8.value) or \
          float_eq (real32_3.value, real32_8.value) or \
          float_eq (real32_4.value, real32_8.value) or \
          float_eq (real32_5.value, real32_8.value) or \
          float_eq (real32_6.value, real32_8.value) or \
          float_eq (real32_7.value, real32_8.value):
        real32_8 = ctypes.c_float (random.uniform (-1e37, 1e37))

    real32a_0 = MI_Real32A ((real32_0.value, real32_1.value, real32_2.value))
    real32a_1 = MI_Real32A ((real32_3.value, real32_4.value, real32_5.value))
    real32a_2 = MI_Real32A ((real32_6.value, real32_7.value, real32_8.value))

    real32a_in = real32a_0
    inst43 = MI_Instance ()
    
    inst43.SetValue ('real32a', real32a_in)
    real32a_out = inst43.GetValue ('real32a')

    if real32a_out is not None:
        if not float_array_eq (real32a_in, real32a_0) or \
               not float_array_eq (inst43.GetValue ('real32a'),real32a_0) or \
               not float_array_eq (real32a_out, real32a_0):
            BookEndPrint ('----- real32a SetValue/GetValue failed')
            rval = False
        else:   
            real32a_in = real32a_1
            if not float_array_eq (real32a_in, real32a_1) or \
                   not float_array_eq (inst43.GetValue ('real32a'), real32a_0) or \
                   not float_array_eq (real32a_out, real32a_0):
                BookEndPrint ('----- real32a SetValue/GetValue stored a reference')
                rval = False
            else:
                real32a_out = real32a_2
                if not float_array_eq (real32a_in, real32a_1) or \
                       not float_array_eq (inst43.GetValue ('real32a'), real32a_0) or \
                       not float_array_eq (real32a_out, real32a_2):
                    BookEndPrint ('----- real32a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- real32a SetValue/GetValue returned None')
        rval = False

    inst44 = MI_Instance ()
    inst44.SetValue ('real32a', inst43.GetValue ('real32a'))
    if float_array_eq (inst44.GetValue ('real32a'), inst43.GetValue ('real32a')):
        inst44.SetValue ('real32a', real32a_1)
        if not float_array_eq (inst44.GetValue ('real32a'), real32a_1):
            BookEndPrint ("----- real32a  SetValue failed")
            rval = False
        if float_array_eq (inst43.GetValue ('real32a'), real32a_1):
            BookEndPrint ('----- real32a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- real32a SetValue/GetValue failed')
        rval = False

    # real64a
    real64_3 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_3) or \
          float_eq (real64_1, real64_3) or \
          float_eq (real64_2, real64_3):
        real64_3 = random.uniform (-1e307, 1e307)
    real64_4 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_4) or \
          float_eq (real64_1, real64_4) or \
          float_eq (real64_2, real64_4) or \
          float_eq (real64_3, real64_4):
        real64_4 = random.uniform (-1e307, 1e307)
    real64_5 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_5) or \
          float_eq (real64_1, real64_5) or \
          float_eq (real64_2, real64_5) or \
          float_eq (real64_3, real64_5) or \
          float_eq (real64_4, real64_5):
        real64_5 = random.uniform (-1e307, 1e307)
    real64_6 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_6) or \
          float_eq (real64_1, real64_6) or \
          float_eq (real64_2, real64_6) or \
          float_eq (real64_3, real64_6) or \
          float_eq (real64_4, real64_6) or \
          float_eq (real64_5, real64_6):
        real64_6 = random.uniform (-1e307, 1e307)
    real64_7 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_7) or \
          float_eq (real64_1, real64_7) or \
          float_eq (real64_2, real64_7) or \
          float_eq (real64_3, real64_7) or \
          float_eq (real64_4, real64_7) or \
          float_eq (real64_5, real64_7) or \
          float_eq (real64_6, real64_7):
        real64_7 = random.uniform (-1e307, 1e307)
    real64_8 = random.uniform (-1e307, 1e307)
    while float_eq (real64_0, real64_8) or \
          float_eq (real64_1, real64_8) or \
          float_eq (real64_2, real64_8) or \
          float_eq (real64_3, real64_8) or \
          float_eq (real64_4, real64_8) or \
          float_eq (real64_5, real64_8) or \
          float_eq (real64_6, real64_8) or \
          float_eq (real64_7, real64_8):
        real64_8 = random.uniform (-1e307, 1e307)

    real64a_0 = MI_Real64A ((real64_0, real64_1, real64_2))
    real64a_1 = MI_Real64A ((real64_3, real64_4, real64_5))
    real64a_2 = MI_Real64A ((real64_6, real64_7, real64_8))

    real64a_in = real64a_0
    inst45 = MI_Instance ()
    
    inst45.SetValue ('real64a', real64a_in)
    real64a_out = inst45.GetValue ('real64a')

    if real64a_out is not None:
        if not float_array_eq (real64a_in, real64a_0) or \
               not float_array_eq (inst45.GetValue ('real64a'),real64a_0) or \
               not float_array_eq (real64a_out, real64a_0):
            BookEndPrint ('----- real64a SetValue/GetValue failed')
            rval = False
        else:   
            real64a_in = real64a_1
            if not float_array_eq (real64a_in, real64a_1) or \
                   not float_array_eq (inst45.GetValue ('real64a'), real64a_0) or \
                   not float_array_eq (real64a_out, real64a_0):
                BookEndPrint ('----- real64a SetValue/GetValue stored a reference')
                rval = False
            else:
                real64a_out = real64a_2
                if not float_array_eq (real64a_in, real64a_1) or \
                       not float_array_eq (inst45.GetValue ('real64a'), real64a_0) or \
                       not float_array_eq (real64a_out, real64a_2):
                    BookEndPrint ('----- real64a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- real64a SetValue/GetValue returned None')
        rval = False

    inst46 = MI_Instance ()
    inst46.SetValue ('real64a', inst45.GetValue ('real64a'))
    if float_array_eq (inst46.GetValue ('real64a'), inst45.GetValue ('real64a')):
        inst46.SetValue ('real64a', real64a_1)
        if not float_array_eq (inst46.GetValue ('real64a'), real64a_1):
            BookEndPrint ("----- real64a  SetValue failed")
            rval = False
        if float_array_eq (inst45.GetValue ('real64a'), real64a_1):
            BookEndPrint ('----- real64a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- real64a SetValue/GetValue failed')
        rval = False

    # char16a
    char16_3 = random.randint (0, 0xFFFF)
    while char16_0 == char16_3 or \
          char16_1 == char16_3 or \
          char16_2 == char16_3:
        char16_3 = random.randint (0, 0xFFFF)
    char16_4 = random.randint (0, 0xFFFF)
    while char16_0 == char16_4 or \
          char16_1 == char16_4 or \
          char16_2 == char16_4 or \
          char16_3 == char16_4:
        char16_4 = random.randint (0, 0xFFFF)
    char16_5 = random.randint (0, 0xFFFF)
    while char16_0 == char16_5 or \
          char16_1 == char16_5 or \
          char16_2 == char16_5 or \
          char16_3 == char16_5 or \
          char16_4 == char16_5:
        char16_5 = random.randint (0, 0xFFFF)
    char16_6 = random.randint (0, 0xFFFF)
    while char16_0 == char16_6 or \
          char16_1 == char16_6 or \
          char16_2 == char16_6 or \
          char16_3 == char16_6 or \
          char16_4 == char16_6 or \
          char16_5 == char16_6:
        char16_6 = random.randint (0, 0xFFFF)
    char16_7 = random.randint (0, 0xFFFF)
    while char16_0 == char16_7 or \
          char16_1 == char16_7 or \
          char16_2 == char16_7 or \
          char16_3 == char16_7 or \
          char16_4 == char16_7 or \
          char16_5 == char16_7 or \
          char16_6 == char16_7:
        char16_7 = random.randint (0, 0xFFFF)
    char16_8 = random.randint (0, 0xFFFF)
    while char16_0 == char16_8 or \
          char16_1 == char16_8 or \
          char16_2 == char16_8 or \
          char16_3 == char16_8 or \
          char16_4 == char16_8 or \
          char16_5 == char16_8 or \
          char16_6 == char16_8 or \
          char16_7 == char16_8:
        char16_8 = random.randint (0, 0xFFFF)

    char16a_0 = MI_Char16A ((char16_0, char16_1, char16_2))
    char16a_1 = MI_Char16A ((char16_3, char16_4, char16_5))
    char16a_2 = MI_Char16A ((char16_6, char16_7, char16_8))

    char16a_in = char16a_0
    inst47 = MI_Instance ()
    
    inst47.SetValue ('char16a', char16a_in)
    char16a_out = inst47.GetValue ('char16a')

    if char16a_out is not None:
        if not array_eq (char16a_in, char16a_0) or \
               not array_eq (inst47.GetValue ('char16a'),char16a_0) or \
               not array_eq (char16a_out, char16a_0):
            BookEndPrint ('----- char16a SetValue/GetValue failed')
            rval = False
        else:   
            char16a_in = char16a_1
            if not array_eq (char16a_in, char16a_1) or \
                   not array_eq (inst47.GetValue ('char16a'), char16a_0) or \
                   not array_eq (char16a_out, char16a_0):
                BookEndPrint ('----- char16a SetValue/GetValue stored a reference')
                rval = False
            else:
                char16a_out = char16a_2
                if not array_eq (char16a_in, char16a_1) or \
                       not array_eq (inst47.GetValue ('char16a'), char16a_0) or \
                       not array_eq (char16a_out, char16a_2):
                    BookEndPrint ('----- char16a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- char16a SetValue/GetValue returned None')
        rval = False

    inst48 = MI_Instance ()
    inst48.SetValue ('char16a', inst47.GetValue ('char16a'))
    if array_eq (inst48.GetValue ('char16a'), inst47.GetValue ('char16a')):
        inst48.SetValue ('char16a', char16a_1)
        if not array_eq (inst48.GetValue ('char16a'), char16a_1):
            BookEndPrint ("----- char16a  SetValue failed")
            rval = False
        if array_eq (inst47.GetValue ('char16a'), char16a_1):
            BookEndPrint ('----- char16a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- char16a SetValue/GetValue failed')
        rval = False
        
    # datetimea
    datetime_3 = MI_Interval ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49))
    datetime_4 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))
    datetime_5 = MI_Interval ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49))
    datetime_6 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))
    datetime_7 = MI_Interval ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49))
    datetime_8 = MI_Timestamp ( \
        random.randint (0, 9), \
        random.randint (10, 19), \
        random.randint (20, 29), \
        random.randint (30, 39), \
        random.randint (40, 49), \
        random.randint (50, 59), \
        random.randint (60, 69), \
        random.randint (70, 79))

    datetimea_0 = MI_DatetimeA ((datetime_0, datetime_1, datetime_2))
    datetimea_1 = MI_DatetimeA ((datetime_3, datetime_4, datetime_5))
    datetimea_2 = MI_DatetimeA ((datetime_6, datetime_7, datetime_8))

    datetimea_in = datetimea_0
    inst49 = MI_Instance ()
    
    inst49.SetValue ('datetimea', datetimea_in)
    datetimea_out = inst49.GetValue ('datetimea')

    if datetimea_out is not None:
        if not datetime_array_eq (datetimea_in, datetimea_0) or \
               not datetime_array_eq (inst49.GetValue ('datetimea'),datetimea_0) or \
               not datetime_array_eq (datetimea_out, datetimea_0):
            BookEndPrint ('----- datetimea SetValue/GetValue failed')
            rval = False
        else:   
            datetimea_in = datetimea_1
            if not datetime_array_eq (datetimea_in, datetimea_1) or \
                   not datetime_array_eq (inst49.GetValue ('datetimea'), datetimea_0) or \
                   not datetime_array_eq (datetimea_out, datetimea_0):
                BookEndPrint ('----- datetimea SetValue/GetValue stored a reference')
                rval = False
            else:
                datetimea_out = datetimea_2
                if not datetime_array_eq (datetimea_in, datetimea_1) or \
                       not datetime_array_eq (inst49.GetValue ('datetimea'), datetimea_0) or \
                       not datetime_array_eq (datetimea_out, datetimea_2):
                    BookEndPrint ('----- datetimea SetValue/GetValue stored a reference')
                    rval = False
                else:
                    datetimea_out = inst49.GetValue ('datetimea')
                    datetimea_out.setValueAt (0, datetime_2)
                    if datetime_array_eq (datetimea_out, inst49.GetValue ('datetimea')) or \
                       datetime_array_eq (datetimea_out, datetimea_2):
                        BookEndPrint ('----- datetimea SetValue/GetValue stored a reference')
                        rval = False
    else:
        BookEndPrint ('----- datetimea SetValue/GetValue returned None')
        rval = False

    inst50 = MI_Instance ()
    inst50.SetValue ('datetimea', inst49.GetValue ('datetimea'))
    if datetime_array_eq (inst50.GetValue ('datetimea'), inst49.GetValue ('datetimea')):
        inst50.SetValue ('datetimea', datetimea_1)
        if not datetime_array_eq (inst50.GetValue ('datetimea'), datetimea_1):
            BookEndPrint ("----- datetimea  SetValue failed")
            rval = False
        if datetime_array_eq (inst49.GetValue ('datetimea'), datetimea_1):
            BookEndPrint ('----- datetimea SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- datettimea SetValue/GetValue failed')
        rval = False

    # stringa
    string_0 = random.randint (0, len (string_vals) - 1)
    temp = string_vals[0]
    string_vals[0] = string_vals[string_0]
    string_vals[string_0] = temp
    string_1 = random.randint (1, len (string_vals) -1)
    temp = string_vals[1]
    string_vals[1] = string_vals[string_1]
    string_vals[string_1] = temp
    string_2 = random.randint (2, len (string_vals) -1)
    temp = string_vals[2]
    string_vals[2] = string_vals[string_2]
    string_vals[string_2] = temp
    string_3 = random.randint (3, len (string_vals) -1)
    temp = string_vals[3]
    string_vals[3] = string_vals[string_3]
    string_vals[string_3] = temp
    string_4 = random.randint (4, len (string_vals) -1)
    temp = string_vals[4]
    string_vals[4] = string_vals[string_4]
    string_vals[string_4] = temp
    string_5 = random.randint (5, len (string_vals) -1)
    temp = string_vals[5]
    string_vals[5] = string_vals[string_5]
    string_vals[string_5] = temp
    string_6 = random.randint (6, len (string_vals) -1)
    temp = string_vals[6]
    string_vals[6] = string_vals[string_6]
    string_vals[string_6] = temp
    string_7 = random.randint (7, len (string_vals) -1)
    temp = string_vals[7]
    string_vals[7] = string_vals[string_7]
    string_vals[string_7] = temp
    string_8 = random.randint (8, len (string_vals) -1)
    temp = string_vals[8]
    string_vals[8] = string_vals[string_8]
    string_vals[string_8] = temp

    stringa_0 = MI_StringA ([string_vals[string_0], string_vals[string_1], \
                             string_vals[string_2]])
    stringa_1 = MI_StringA ([string_vals[string_3], string_vals[string_4], \
                             string_vals[string_5]])
    stringa_2 = MI_StringA ([string_vals[string_6], string_vals[string_7], \
                             string_vals[string_8]])

    stringa_in = stringa_0
    inst51 = MI_Instance ()
    
    inst51.SetValue ('stringa', stringa_in)
    stringa_out = inst51.GetValue ('stringa')

    if stringa_out is not None:
        if not array_eq (stringa_in, stringa_0) or \
               not array_eq (inst51.GetValue ('stringa'),stringa_0) or \
               not array_eq (stringa_out, stringa_0):
            BookEndPrint ('----- stringa SetValue/GetValue failed')
            rval = False
        else:   
            stringa_in = stringa_1
            if not array_eq (stringa_in, stringa_1) or \
                   not array_eq (inst51.GetValue ('stringa'), stringa_0) or \
                   not array_eq (stringa_out, stringa_0):
                BookEndPrint ('----- stringa SetValue/GetValue stored a reference')
                rval = False
            else:
                stringa_out = stringa_2
                if not array_eq (stringa_in, stringa_1) or \
                       not array_eq (inst51.GetValue ('stringa'), stringa_0) or \
                       not array_eq (stringa_out, stringa_2):
                    BookEndPrint ('----- stringa SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- stringa SetValue/GetValue returned None')
        rval = False

    inst52 = MI_Instance ()
    inst52.SetValue ('stringa', inst51.GetValue ('stringa'))
    if array_eq (inst52.GetValue ('stringa'), inst51.GetValue ('stringa')):
        inst52.SetValue ('stringa', stringa_1)
        if not array_eq (inst52.GetValue ('stringa'), stringa_1):
            BookEndPrint ("----- stringa  SetValue failed")
            rval = False
        if array_eq (inst51.GetValue ('stringa'), stringa_1):
            BookEndPrint ('----- stringa SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- stringa SetValue/GetValue failed')
        rval = False
    
    # MI_Uint8A
    # uint8a
    # inst27
    # inst28

    
    return rval


####################################


def fn1 ():
    be = BookEnd ('fn1')

    #qualDecl0 = MI_QualifierDecl ('alpha', MI_STRING, 2, 3, 'monkey')
    #qual0 = MI_Qualifier ('bravo', MI_STRING, 2, 'taco')

    #qualifiers = [MI_Qualifier ('charlie', MI_STRING, 3, 'cheese')]

    #propDecl0 = MI_PropertyDecl (3, 4, 'delta', qualifiers, MI_STRING, 'echo')

    #parameters = [MI_ParameterDecl (5, 6, 'fox', qualifiers, MI_STRING, 'golf')]

    #meth0 = MI_MethodDecl (7, 8, 'hotel', qualifiers, parameters, MI_UINT32,
    #                       'origin', 'propagator')

    #val = MI_Uint32 (1)
    #BookEndPrint ('val: {0}'.format (val))


    # uint8a
    uint8_0 = random.randint (0, 0xFF)
    uint8_1 = random.randint (0, 0xFF)
    while uint8_1 == uint8_0:
        uint8_1 = random.randint (0, 0xFF)
    uint8_2 = random.randint (0, 0xFF)
    while uint8_2 == uint8_0 or \
          uint8_2 == uint8_1:
        uint8_2 = random.randint (0, 0xFF)
    uint8_3 = random.randint (0, 0xFF)
    while uint8_0 == uint8_3 or \
          uint8_1 == uint8_3 or \
          uint8_2 == uint8_3:
        uint8_3 = random.randint (0, 0xFF)
    uint8_4 = random.randint (0, 0xFF)
    while uint8_0 == uint8_4 or \
          uint8_1 == uint8_4 or \
          uint8_2 == uint8_4 or \
          uint8_3 == uint8_4:
        uint8_4 = random.randint (0, 0xFF)
    uint8_5 = random.randint (0, 0xFF)
    while uint8_0 == uint8_5 or \
          uint8_1 == uint8_5 or \
          uint8_2 == uint8_5 or \
          uint8_3 == uint8_5 or \
          uint8_4 == uint8_5:
        uint8_5 = random.randint (0, 0xFF)
    uint8_6 = random.randint (0, 0xFF)
    while uint8_0 == uint8_6 or \
          uint8_1 == uint8_6 or \
          uint8_2 == uint8_6 or \
          uint8_3 == uint8_6 or \
          uint8_4 == uint8_6 or \
          uint8_5 == uint8_6:
        uint8_6 = random.randint (0, 0xFF)
    uint8_7 = random.randint (0, 0xFF)
    while uint8_0 == uint8_7 or \
          uint8_1 == uint8_7 or \
          uint8_2 == uint8_7 or \
          uint8_3 == uint8_7 or \
          uint8_4 == uint8_7 or \
          uint8_5 == uint8_7 or \
          uint8_6 == uint8_7:
        uint8_7 = random.randint (0, 0xFF)
    uint8_8 = random.randint (0, 0xFF)
    while uint8_0 == uint8_8 or \
          uint8_1 == uint8_8 or \
          uint8_2 == uint8_8 or \
          uint8_3 == uint8_8 or \
          uint8_4 == uint8_8 or \
          uint8_5 == uint8_8 or \
          uint8_6 == uint8_8 or \
          uint8_7 == uint8_8:
        uint8_8 = random.randint (0, 0xFF)

    uint8a_0 = MI_Uint8A ((uint8_0, uint8_1, uint8_2))
    uint8a_1 = MI_Uint8A ((uint8_3, uint8_4, uint8_5))
    uint8a_2 = MI_Uint8A ((uint8_6, uint8_7, uint8_8))

    uint8a_in = uint8a_0
    inst27 = MI_Instance ()
    
    inst27.SetValue ('uint8a', uint8a_in)
    uint8a_out = inst27.GetValue ('uint8a')

    if uint8a_out is not None:
        if not array_eq (uint8a_in, uint8a_0) or \
               not array_eq (inst27.GetValue ('uint8a'),uint8a_0) or \
               not array_eq (uint8a_out, uint8a_0):
            BookEndPrint ('----- uint8a SetValue/GetValue failed')
            rval = False
        else:   
            uint8a_in = uint8a_1
            if not array_eq (uint8a_in, uint8a_1) or \
                   not array_eq (inst27.GetValue ('uint8a'), uint8a_0) or \
                   not array_eq (uint8a_out, uint8a_0):
                BookEndPrint ('----- uint8a SetValue/GetValue stored a reference')
                rval = False
            else:
                uint8a_out = uint8a_2
                if not array_eq (uint8a_in, uint8a_1) or \
                       not array_eq (inst27.GetValue ('uint8a'), uint8a_0) or \
                       not array_eq (uint8a_out, uint8a_2):
                    BookEndPrint ('----- uint8a SetValue/GetValue stored a reference')
                    rval = False
    else:
        BookEndPrint ('----- uint8a SetValue/GetValue returned None')
        rval = False

    inst28 = MI_Instance ()
    inst28.SetValue ('uint8a', inst27.GetValue ('uint8a'))
    if array_eq (inst28.GetValue ('uint8a'), inst27.GetValue ('uint8a')):
        inst28.SetValue ('uint8a', uint8a_1)
        if not array_eq (inst28.GetValue ('uint8a'), uint8a_1):
            BookEndPrint ("----- uint8a  SetValue failed")
            rval = False
        if array_eq (inst27.GetValue ('uint8a'), uint8a_1):
            BookEndPrint ('----- uint8a SetValue/GetValue stored a reference')
            rval = False
    else:
        BookEndPrint ('----- uint8a SetValue/GetValue failed')
        rval = False
    


def main (argv = None):
    be = BookEnd ('main')

    rval = True
    
    if False == bool_test ():
        rval = False
    if False == uint8_test ():
        rval = False
    if False == sint8_test ():
        rval = False
    if False == uint16_test ():
        rval = False
    if False == sint16_test ():
        rval = False
    if False == uint32_test ():
        rval = False
    if False == sint32_test ():
        rval = False
    if False == uint64_test ():
        rval = False
    if False == sint64_test ():
        rval = False
    if False == real32_test ():
        rval = False
    if False == real64_test ():
        rval = False
    if False == char16_test ():
        rval = False
    if False == timestamp_test ():
        rval = False
    if False == interval_test ():
        rval = False
    if False == string_test ():
        rval = False

    if False == booleana_test ():
        rval = False
    if False == uint8a_test ():
        rval = False
    if False == sint8a_test ():
        rval = False
    if False == uint16a_test ():
        rval = False
    if False == sint16a_test ():
        rval = False
    if False == uint32a_test ():
        rval = False
    if False == sint32a_test ():
        rval = False
    if False == uint64a_test ():
        rval = False
    if False == sint64a_test ():
        rval = False
    if False == real32a_test ():
        rval = False
    if False == real64a_test ():
        rval = False
    if False == char16a_test ():
        rval = False
    if False == datetimea_test ():
        rval = False
    if False == stringa_test ():
        rval = False

    if False == instance_test ():
        rval = False

    BookEndPrint ('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
    BookEndPrint ('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
    if not rval:
        BookEndPrint ('!!!!!  Tests have failed!  !!!!!')
    else:
        BookEndPrint ('!!!!!  All tests passed!   !!!!!')
    BookEndPrint ('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
    BookEndPrint ('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')


    #fn1 ()


if __name__ == '__main__':
    sys.exit (main (sys.argv))
