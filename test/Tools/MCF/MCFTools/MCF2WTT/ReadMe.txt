MCF2WTT
--------
Summary:
MCF2WTT Log tool converts MCF style log files to WTT 2.2 log or greater format.

USAGE:
  MCF2WTTLog.exe /m:<MCFLog.xml> /w:<WTTLog.wtl>
  /m Path to MCF Log file; Must include full path if not in the same directory
  /w Desired output file name; Default will be WTTLog.wtl if unspecified
  /? Displays usage


DEFINED ERROR CODES:
The following is a list of possible error codes which are returned by MCF2WTTLog.exe. The tool doesn't throw exceptions.
However if an error occurred during processing the input file the tool returns S_OK to indicate successful execution. The output file will contain a log of all errors encountered during processing the log file.
An UNKNOWN_ERROR code is returned for unhandled exceptions. 

1. S_OK = 0;            //Success. No errors.
2. PARSE_ERROR  = -1;   //Could not parse command line arguments, most likely the input file names
3. IO_ERROR = -2;       //Input/Output error: File not found, IO Exceptions etc
4. FILERW_ERROR = -3;   //File Read/Write Errors
5. UNKNOWN_ERROR = -4;  //Needs further investigation, generic error
6. FORMAT_ERROR = -5;   //Input XML format wasn't well formed XML.


Assumptions:
1. Both MCF and WTT log files are on the local system. Running the tool over a network isn't supported and hasn't been tested.

2. MCF log files are supplied with the .xml extension and WTT Log files are output with a .wtl extension. 
The tool will append missing extensions to the input and output files if they are ommited. 

3. The output file extension can't be overriden at this time. i.e The /W flag will always output a file with a .wtl extension. However to view in raw XML, simply rename from .wtl to .xml

4. The tool uses the following mapping for the text within the following  MCF elements:
    Msg         --> WTT Trace Message
    Rec         --> WTT Trace Message
    Trace       --> WTT Trace Message
    Result      --> End Test
    Repro       --> WTT Trace Message
    Error       --> WTT Trace Exception
    Exception   --> WTT Trace Exception
    Counter     --> WTT PFRollUp Tag
    Step        --> Not processed
    Fnc         --> Not processed
    Group       --> Not Processed
    TestCase    --> Not processed
    MetaData    --> Not Processed
    MachineName --> Not processed (included in WTT Machine Tag)
    OS          --> Not processed (included in WTT Machine Tag)
    Run	        --> Not Processed
    Runs        --> Not Processed
    
Any elements which aren't processed (either due to explicit exclusion or lack of a direct WTT logger mapping) and which contain text are processed as WTT trace messages as follows: 
USER DEFINED: [ElementName]: Value. For example:
<Started Cat="Alw">12/7/2007 9:46:13 AM</Started> will converted to a message and appear as: 
USER DEFINED: Started: 12/7/2007 9:46:13 AM 

5. Special processing is used to apply the override the PFRollup Tag and to create the EndTest tag in the WTT attributes.

6. The End Test tag is also generated based on attributes in the <Result> element. 

7. The WTT PFRollup tag is overridden. However as a default, there will always be a 2nd WTT supplied PFRollup tag.

8. This tool writes a Machine element which contains all relevant information on the execution environment. This is done via system calls hence in order to get an accurate representation of the environment, run this tool on the system where the test case was executed.

9. WTT studio doesn't propagate warnings and blocked test cases in the UI.  Thus, the tool has been modified to treat all warnings, failed and blocked cases as failures. To compensate for this, the actual pass/fail breakdown is included in the log file just before the pass/fail rollup information.
Contact: dmallum with any questions.