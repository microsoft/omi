/* Stand-alone program to test PAM installation/configuration.
 * Program can be built via:  gcc -o pamtest pamtest.c -lpam
 * This program should be executed with root permission:
 * i.e. sudo pamtest <user> <passwd>
 */

#include <security/pam_appl.h>

static int _authCallback(
    int numMessages,
#if defined(CONFIG_OS_LINUX) || defined(CONFIG_OS_DARWIN) || defined(CONFIG_OS_BSD)
    const struct pam_message** messages,
#else
    struct pam_message** messages,
#endif
    struct pam_response** response,
    void* applicationData)
{
    const char* password = (const char*)applicationData;
    int i;

    /* If zero (or negative) messages, return now */

    if (numMessages <= 0)
    {
        return PAM_CONV_ERR;
    }

    /* Allocate the responses */

    *response = (struct pam_response*)calloc(
        numMessages, 
        sizeof(struct pam_response));

    if (!*response)
    {
        return PAM_BUF_ERR;
    }

    /* Copy the password to the response messages */

    for (i = 0; i < numMessages; i++)
    {
        if (PAM_PROMPT_ECHO_OFF == messages[i]->msg_style)
        {
            response[i]->resp = (char*)malloc(PAM_MAX_MSG_SIZE);
            strncpy(response[i]->resp, password, PAM_MAX_MSG_SIZE);
            response[i]->resp_retcode = 0;
        }
        else
        {
            return PAM_CONV_ERR;
        }
    }

    return PAM_SUCCESS;
}

int main(int argc, char**argv)
{
    const char* user = argv[1];
    const char* password = argv[2];

    struct pam_conv conv;
    pam_handle_t* t = 0;

    memset(&conv, 0, sizeof(conv));

    conv.conv = _authCallback;
    conv.appdata_ptr = (void*)password;

    int r = pam_start("omi", user, &conv, &t);
    if (PAM_SUCCESS != r)
    {
        printf("pam_start failed: %d\n", r);
        return -1;
    }

    r = pam_authenticate(t, 0);
    if (PAM_SUCCESS != r)
    {
        pam_end(t,0);
        printf("pam_authenticate failed: %d\n", r);
        return -1;
    }

    r = pam_acct_mgmt(t, 0);
    if (PAM_SUCCESS != r)
    {
        pam_end(t,0);
        printf("pam_acct_mgmt failed: %d\n", r);
        return -1;
    }

    pam_end(t, 0);

    printf("Success!!!\n");
    return 0;
}
