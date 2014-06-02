#include <vector>
#include <cassert>
#include "ABC_Widget.h"
#include "ABC_Gadget.h"
#include "ABC_Connector.h"
#include <ut/ut.h>

using namespace std;
using namespace mi;

#if 0
static void Dump(const vector<ABC_Connector_Class>& v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        v[0].Print();
    }
}
#endif

NitsSetup(MapOfInstancesSetup)
NitsEndSetup

NitsCleanup(MapOfInstancesSetup)
NitsEndCleanup

NitsTestWithSetup(Test1, MapOfInstancesSetup)
{
    vector<ABC_Connector_Class> v;

    // Insert a connector into the STL vector:
    {
        ABC_Widget_Class w;
        w.Key_value(MI_T("1000"));
        w.Color_value(MI_T("Red"));

        ABC_Gadget_Class g;
        g.Key_value(MI_T("1000"));
        g.Color_value(MI_T("Blue"));

        ABC_Connector_Class c;
        w.__setCopyOnWrite(false);
        assert(w.__getCopyOnWrite() == false);
        c.Left_value(w);
        g.__setCopyOnWrite(false);
        assert(g.__getCopyOnWrite() == false);
        c.Right_value(g);

        v.push_back(c);
    }

    // Update v[0]:
    ABC_Connector_Class c = v[0];

    ABC_Widget_Class w = c.Left_value();
    w.Color_value(MI_T("Pink"));

    ABC_Gadget_Class g = c.Right_value();
    g.Color_value(MI_T("Cyan"));

    // Dump the vector:
    UT_ASSERT(v[0].Left_value().Color_value() == MI_T("Pink"));
    UT_ASSERT(v[0].Right_value().Color_value() == MI_T("Cyan"));

    // Test __forceCopyOnWrite()
    {
        ABC_Widget_Class w1;
        w1.Key_value(MI_T("1000"));
        w1.Color_value(MI_T("Red"));
        w1.__setCopyOnWrite(false);


        ABC_Widget_Class w2 = w1;
        w2.__forceCopyOnWrite();
        w2.Color_value(MI_T("Pink"));
#if 0
        w1.Print();
        w2.Print();
#endif

        UT_ASSERT(w1.Color_value() == MI_T("Red"));
        UT_ASSERT(w2.Color_value() == MI_T("Pink"));
    }
}
NitsEndTest
