/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdlib.h>
#include <micodec.h>

/*=============================================================================
**
** Structure hold objects for creating mof deserializer
**
=============================================================================*/
typedef struct _MofCodecer
{
    MI_Application app;
    MI_Boolean appcreated;
    MI_OperationOptions options;
    MI_Boolean optionscreated;
    MI_Deserializer de;
    MI_Boolean decreated;
}MofCodecer;

/*=============================================================================
**
** Created deserializer
**
=============================================================================*/
MI_Result CreateMofCodecer(_Inout_ MofCodecer * self)
{
    MI_Result r;
    r = MI_Application_Initialize(0, MI_T("test"), NULL, &self->app);
    if (r!=MI_RESULT_OK) return r;
    self->appcreated = MI_TRUE;
    r = MI_Application_NewOperationOptions(&self->app, MI_FALSE, &self->options);
    if (r!=MI_RESULT_OK) return r;
    self->optionscreated = MI_TRUE;

    /* Please look at micodec.h for all supported schema validation options */
    r = MI_OperationOptions_SetString(&self->options, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, MOFCODEC_SCHEMA_VALIDATION_IGNORE, 0);
    if (r!=MI_RESULT_OK) return r;
    r = MI_Application_NewDeserializer_Mof(&self->app, 0, MOFCODEC_FORMAT, &self->de);
    if (r!=MI_RESULT_OK) return r;
    self->decreated = MI_TRUE;
    return MI_RESULT_OK;
}

/*=============================================================================
**
** Finalize deserializer
**
=============================================================================*/
void DeleteMofCodecer(_Inout_ MofCodecer * self)
{
    if (self->optionscreated) MI_OperationOptions_Delete(&self->options);
    if (self->decreated) MI_Deserializer_Close(&self->de);
    if (self->appcreated) MI_Application_Close(&self->app);
}

/*=============================================================================
**
** Deserialize class and instance
**
=============================================================================*/
void DeserializeClassAndInstance()
{
    MI_ClassA *ca = NULL;
    MI_InstanceA *ia = NULL;
    MofCodecer codecer = {0};
    MI_Uint32 i;

    /* create deserializer */
    MI_Result r = CreateMofCodecer(&codecer);
    if( r != MI_RESULT_OK )
    {
        printf("Create mof deserializer failed");
        return;
    }

    do
    {
        /* deserialize class */
        {
            char classmof[] = "class MSFT_Embedded {string name;};\n"
                "    class MSFT_Test {[EmbeddedInstance(\"MSFT_Embedded\")] string object;};";
            MI_Uint32 length = (MI_Uint32)sizeof(classmof);
            MI_Uint32 readBytes;

            printf("START TO DESERIALIZE class mof :\n    %s\n\n", classmof);

            r = MI_Application_NewDeserializer_Mof(&codecer.app, 0, MOFCODEC_FORMAT, &codecer.de);
            if( r != MI_RESULT_OK )
            {
                printf("Create mof deserializer failed");
                break;
            }

            r = MI_Deserializer_DeserializeClassArray(&codecer.de, 0, &codecer.options, 0, (MI_Uint8*)classmof, (MI_Uint32)length, NULL, NULL, NULL, &readBytes, &ca, NULL);
            if( r != MI_RESULT_OK )
            {
                printf("deserialize class failed");
                break;
            }

            printf("Deserialized %d class(es), input buffer size (%d), read buffer size (%d):\n", ca->size, length, readBytes);
            for (i = 0; i < ca->size; i++)
            {
                printf("    No {%d} class name is '%S'\n", i, ca->data[i]->classDecl->name);
            }
        }

        printf("\n\n\n");

        /* deserialize insance */
        {
            char instmof[] = "instance of MSFT_Embedded as $x{name=\"abc\";};\n"
                             "    instance of MSFT_Test {object=$x;};";
            MI_Uint32 length = (MI_Uint32)sizeof(instmof);
            MI_Uint32 readBytes;

            printf("START TO DESERIALIZE instance mof :\n    %s\n\n", instmof);

            r = MI_Application_NewDeserializer_Mof(&codecer.app, 0, MOFCODEC_FORMAT, &codecer.de);
            if( r != MI_RESULT_OK )
            {
                printf("Create mof deserializer failed");
                break;
            }

            r = MI_Deserializer_DeserializeInstanceArray(&codecer.de, 0, &codecer.options, 0, (MI_Uint8*)instmof, (MI_Uint32)length, ca, &readBytes, &ia, NULL);
            if( r != MI_RESULT_OK )
            {
                printf("deserialize instance failed");
                break;
            }

            printf("Deserialized %d instance(s), input buffer size (%d), read buffer size (%d):\n", ia->size, length, readBytes);
            for (i = 0; i < ia->size; i++)
            {
                printf("    No {%d} instance's class name is '%S'\n", i, ia->data[i]->classDecl->name);
            }
        }
    }while(0);

    /* free resources */
    if (ia)
    {
        MI_Deserializer_ReleaseInstanceArray(ia);
    }
    if (ca)
    {
        MI_Deserializer_ReleaseClassArray(ca);
    }
    DeleteMofCodecer(&codecer);
}

/*=============================================================================
**
** Entry of the application
**
=============================================================================*/
int MI_MAIN_CALL main(int argc, _In_reads_z_(argc) const char** argv)
{
    MI_UNREFERENCED_PARAMETER(argc);
    MI_UNREFERENCED_PARAMETER(argv);
    DeserializeClassAndInstance();
    return 0;
}
