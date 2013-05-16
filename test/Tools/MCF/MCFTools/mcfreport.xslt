<?xml version="1.0" encoding="UTF-8" ?>
<!-- This XSL file is used to convert an MCF structured XML report to a readable html document-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:msxsl="urn:schemas-microsoft-com:xslt"
                xmlns:user="http://mycompany.com/mynamespace"
                version="1.0">
  <xsl:output method="xml"/>

  <xsl:template name="root" match="/">
    <html>
      <head>
        <title>Test Result Report</title>
        <meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR"/>
        <meta content="C#" name="CODE_LANGUAGE"/>
        <meta content="JavaScript" name="vs_defaultClientScript"/>
        <meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema"/>

        <script language="javascript">
          <![CDATA[
          function toggleDisp(element) {
            if(element.style.display == 'none') {
              element.style.display='';
            }
            else
            {
             element.style.display='none';
            }
          }
          
          function toggleActive(tab) {
            if(tab.className == 'Tabs_active') {
              tab.className = 'Tabs_inactive';
            }
            else
            {
              tab.className = 'Tabs_active';
            }
          }
          ]]>
        </script>

        <style type="text/css">
          .Tabs_active
          {
          cursor:hand;
          border: inset 1px;
          }
          .Tabs_inactive
          {
          cursor:hand;
          border: outset 1px;
          }
          .Error
          {
          color:red;
          border:none;
          padding:1px;
          }
          .Msg
          {
          color:black;
          border:none;
          padding:1px;
          }
          .Trace
          {
          color:gray;
          border:none;
          padding:1px;
          }
          .Comment
          {
          color:blue;
          border:none;
          padding:1px;
          }
          pre
          {
          white-space:pre-wrap;
          word-wrap:break-word;
          font-family:'Courier New';
          }
          table
          {
          border:2px outset #93BEE2;
          font-size:10pt;
          font-family:tahoma;
          border-collapse:collapse;
          border-color:gray;
          }
          th
          {
          border:2px solid;
          border-color:gray;
          padding:5px;
          font-weight:bold;
          background-color:#0000FF;
          color:#FFFFF6;
          }
          td
          {
          border:1px solid;
          border-color:gray;
          padding:4px;
          }
          tr
          {
          vertical-align: top;
          }
        </style>
      </head>
      <body>
        <p id="activex_info" extra="true">
        This document contains javascript controls that are currently disabled. By allowing these blocked ActiveX 
        controls, buttons will be enabled to show messages, trace statements, and comments from MCF.
        </p>

        <script>
          toggleDisp(activex_info)
        </script>
        
        <xsl:for-each select="//Run">
          <table width="99%">
            <tr>
              <td class="Tabs_active" width="99%">
                <xsl:attribute name="onclick">
                  toggleDisp(R<xsl:number value="position()" />Content)
                </xsl:attribute>
                Test pass R<xsl:number value="position()" />
                <xsl:value-of select="./Repro" />
              </td>
            </tr>
          </table>
          <table width="99%">
            <xsl:attribute name="id">R<xsl:number value="position()" />Content</xsl:attribute>
            <xsl:call-template name="Node">
              <xsl:with-param name="id">R<xsl:number value="position()" /></xsl:with-param>
            </xsl:call-template>
          </table>
        </xsl:for-each>
      </body>
    </html>
  </xsl:template>

  <xsl:template name="Node" match="*">
    <xsl:param name="id"></xsl:param>
    
    <!-- Write any header information for the node -->
    <xsl:if test="./*">
      <xsl:choose>
        <xsl:when test="name() = 'Run'">
          <tr>
            <xsl:attribute name="id"><xsl:value-of select="$id"/>Summary</xsl:attribute>
            <td colspan="4">
              <table width="99%" style="border:none;">
                <tr style="vertical-Align:top;">
                  <td width="20%" style="border:none;">
                    <xsl:call-template name="Results">
                    </xsl:call-template>
                  </td>
                  <td width="20%" style="border:none;"></td>
                  <td width="20%" align="right" style="border:none;">
                    <xsl:call-template name="MetaData">
                    </xsl:call-template>
                  </td>
                </tr>
              </table>
              <br/>
              <xsl:call-template name="Buttons">
                <xsl:with-param name="id" select="$id"/>
              </xsl:call-template>
            </td>
          </tr>
          <tr>
            <th>ID</th>
            <th>Additional Info</th>
            <th>Result</th>
            <th extra="true">Execution Time</th>
          </tr>
        </xsl:when>
        <xsl:when test="name() = 'TestCase'">
          <tr>
            <xsl:choose>
              <xsl:when test="./Result/@Res='VAR_UNSUPPORTED'">
                <xsl:attribute name="style">background-color:#C0C0C0</xsl:attribute>
              </xsl:when>
              <xsl:when test="./Result/@Res='VAR_ABORT'">
                <xsl:attribute name="style">background-color:#FFEEBA</xsl:attribute>
              </xsl:when>
              <xsl:when test="./Result/@BugId">
                <xsl:attribute name="style">background-color:#FFFFAA</xsl:attribute>
              </xsl:when>
              <xsl:when test="./Result/@Res='VAR_FAIL'">
                <xsl:attribute name="style">background-color:#FFBABA</xsl:attribute>
              </xsl:when>
              <xsl:when test="./Result/@Res='VAR_PASS'">
                <xsl:attribute name="style">background-color:#DFFFDF</xsl:attribute>
              </xsl:when>
              <xsl:otherwise>
                <xsl:attribute name="style">background-color:#EFEFF6</xsl:attribute>
              </xsl:otherwise>
            </xsl:choose>
            <!-- Construct the tooltip for testcases -->
            <xsl:attribute name="title">TestCase&#13;<xsl:value-of select="concat(normalize-space(./Result), '&#13;')"/>
            <xsl:value-of select="concat('Set:    ', ./Result/@Set, '&#13;')"/>
            <xsl:value-of select="concat('Lvl:    ', ./Result/@Lvl, '&#13;')"/>
            <xsl:value-of select="concat('VID:    ', ./Result/@VId, '&#13;')"/>
            <xsl:value-of select="concat('PermID: ', ./Result/@PermId, '&#13;')"/>
            <xsl:value-of select="concat('CID:    ', ./Result/@CId, '&#13;')"/>
            </xsl:attribute>
            <td>
              <xsl:value-of select="./Result/@Set"/>.<xsl:value-of select="./Result/@Lvl"/>.<xsl:value-of select="./Result/@VId"/>
              <xsl:if test="./Result/@PermId">
                - <xsl:value-of select="./Result/@PermId"/>
              </xsl:if>
            </td>
            <td width="50%">
              <xsl:value-of select="./Result"/>
              <br/>
              <xsl:call-template name="Buttons">
                <xsl:with-param name="id" select="$id"/>
              </xsl:call-template>
            </td>
            <td>
              <xsl:for-each select="./Result">
                <xsl:if test="./@Res = 'VAR_PASS'">
                  <font style="color:#00AA00">Pass</font>
                  <br />
                </xsl:if>
                <xsl:if test="./@Res = 'VAR_FAIL'">
                  <font style="color:#FF0000">Fail</font>
                  <br />
                </xsl:if>
                <xsl:if test="./@Res = 'VAR_ABORT'">
                  <font style="color:#EE5500">Abort</font>
                  <br />
                </xsl:if>
                <xsl:if test="./@Res = 'VAR_UNSUPPORTED'">
                  <font style="color:#444444">Unsupported</font>
                  <br />
                </xsl:if>
                <xsl:if test="./@Res = 'VAR_NOTRUN'">
                  <xsl:choose>
                    <xsl:when test="./@Mode = 'inactive'">
                      <font style="color:#444444">Disabled</font>
                    </xsl:when>
                    <xsl:otherwise>
                      <font style="color:#444444">Not Run</font>
                    </xsl:otherwise>
                  </xsl:choose>
                  <br />
                </xsl:if>
                <xsl:if test="./@Res = 'VAR_MANUAL'">
                  <font style="color:#444444">Manual</font>
                  <br />
                </xsl:if>
              </xsl:for-each>
              <xsl:if test="./Result/@BugId">
                <xsl:value-of select="./Result/@BugId"/>
              </xsl:if>
            </td>
            <td extra="true">
              <xsl:if test="./Time">
                <xsl:call-template name="time">
                  <xsl:with-param name="timestring" select="./Time[last()]"/>
                </xsl:call-template>
              </xsl:if>
            </td>
          </tr>
        </xsl:when>
        <xsl:when test="name() = 'Group'">
          <tr style="background-color:#3399FF;" extra="true">
            <td>
              <!-- Add markers to indicate the Group's depth. Plus one for the current node. -->
              <xsl:for-each select="ancestor::Group">&gt;</xsl:for-each>&gt;
              <xsl:value-of select="./Result/@GrpId"/>
              <xsl:if test="./Result/@PermId">
                - <xsl:value-of select="./Result/@PermId"/>
              </xsl:if>
            </td>
            <td>
              <xsl:call-template name="Buttons">
                <xsl:with-param name="id" select="$id"/>
              </xsl:call-template>
              &#8195;<xsl:value-of select="./Result"/>
            </td>
            <td>
              <xsl:for-each select="./Result">
                <xsl:if test="./@Res = 'GRP_PASS'">
                  <font style="color:#008800">Group_Pass</font>
                  <br />
                </xsl:if>
                <xsl:if test="./@Res = 'GRP_FAIL'">
                  <font style="color:#CC0000">Group_Fail</font>
                  <br />
                </xsl:if>
                <xsl:if test="./@Res = 'GRP_ABORT'">
                  <font style="color:#CC3300">Group_Abort</font>
                  <br />
                </xsl:if>
              </xsl:for-each>
              <xsl:if test="./Result/@BugId">
                <xsl:value-of select="./Result/@BugId"/>
              </xsl:if>
            </td>
            <td extra="true">
              <xsl:if test="./Time">
                <xsl:call-template name="time">
                  <xsl:with-param name="timestring" select="./Time[last()]"/>
                </xsl:call-template>
              </xsl:if>
            </td>
          </tr>
        </xsl:when>
        <xsl:otherwise>
          <tr style="display:none;">
            <xsl:attribute name="id">
              <xsl:value-of select="$id"/>
            </xsl:attribute>
            <td>
              <xsl:value-of select="name()"/>
            </td>
            <td colspan="4">
              <xsl:call-template name="Buttons">
                <xsl:with-param name="id" select="$id"/>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
    
    <!-- Process any children of the current node -->
    <xsl:for-each select="./*">
      <xsl:choose>
        <xsl:when test="name() = 'TestCase'">
          <xsl:call-template name="Node">
            <xsl:with-param name="id">
              <xsl:value-of select="$id"/>T<xsl:number value="position()"/>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:when>
        <xsl:when test="name() = 'Group'">
          <xsl:call-template name="Node">
            <xsl:with-param name="id">
              <xsl:value-of select="$id"/>G<xsl:number value="position()"/>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:when>
        <xsl:when test="name() = 'Error' or (name() = 'Msg' and @Cat = 'ERR') or (name() = 'Msg' and @Cat = 'Wrn')">
          <tr style="display:none;">
            <xsl:attribute name="id">
              <xsl:value-of select="$id"/>Error<xsl:number value="position()"/>
            </xsl:attribute>
            <td class="Error">
              <xsl:value-of select="./Step/Msg/@TS"/>
            </td>
            <td colspan="3" class="Error">
              <xsl:call-template name="Error">
              </xsl:call-template>
            </td>
          </tr>
        </xsl:when>
        <xsl:when test="name() = 'Msg' and @Cat = 'Alw'">
          <tr style="display:none;">
            <xsl:attribute name="id">
              <xsl:value-of select="$id"/>Msg<xsl:number value="position()"/>
            </xsl:attribute>
            <td class="Msg">
              <xsl:value-of select="./@TS"/>
            </td>
            <td colspan="3" class="Msg">
              <xsl:call-template name="linkify">
                <xsl:with-param name="line">
                  <xsl:value-of select="."/>
                </xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:when>
        <xsl:when test="name() = 'Trace' or (name() = 'Msg' and @Cat = 'Trc')">
          <tr style="display:none;">
            <xsl:attribute name="id">
              <xsl:value-of select="$id"/>Trace<xsl:number value="position()"/>
            </xsl:attribute>
            <td class="Trace">
              <xsl:value-of select="./@TS"/>
            </td>
            <td colspan="3" class="Trace">
              <xsl:call-template name="linkify">
                <xsl:with-param name="line">
                  <xsl:value-of select="."/>
                </xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:when>
        <xsl:when test="name() = 'Comment'">
          <tr style="display:none;">
            <xsl:attribute name="id">
              <xsl:value-of select="$id"/>Comment<xsl:number value="position()"/>
            </xsl:attribute>
            <td class="Comment">
              <xsl:value-of select="./@TS"/>
            </td>
            <td colspan="3" class="Comment">
              <xsl:call-template name="linkify">
                <xsl:with-param name="line">
                  <xsl:value-of select="."/>
                </xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:when>
        <xsl:when test="not(name() = 'TestCase') and not(name() = 'Group') and count(.//*[name() = 'Error' or name() = 'Msg' or name() = 'Trace' or name() = 'Comment']) > 0">
          <xsl:call-template name="Node">
            <xsl:with-param name="id">
              <xsl:value-of select="$id"/>Extra<xsl:number value="position()"/>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:when>
      </xsl:choose>
    </xsl:for-each>
  </xsl:template>
  
  <xsl:template name="Error" match="Error">
    Error:
    <xsl:choose>
      <xsl:when test="name()='Msg'">
        <xsl:call-template name="linkify">
          <xsl:with-param name="line">
            <xsl:value-of select="."/>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:if test="./Step/Msg">
          <br />
          Step <xsl:value-of select="./Step/Msg"/>
        </xsl:if>
        <xsl:if test="./Fnc/Msg">
          <br />
          Fnc: <xsl:value-of select="./Fnc/Msg"/>
        </xsl:if>
        <xsl:for-each select="./Exception">
          <pre style="white-space:normal">
            <xsl:call-template name="format-linebreaks">
              <xsl:with-param name="text" select="."/>
            </xsl:call-template>
          </pre>
        </xsl:for-each>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="Buttons" match="*">
    <xsl:param name="id"></xsl:param>
    <a class="Tabs_inactive" style="display:none;background-color:#FFDFDF;">
      <xsl:attribute name="id"><xsl:value-of select="$id"/>Error</xsl:attribute>
      <xsl:attribute name="onclick">
        toggleActive(<xsl:value-of select="$id"/>Error)
        <xsl:for-each select="./*">
          <xsl:if test="name() = 'Error' or (name() = 'Msg' and @Cat = 'ERR')  or (name() = 'Msg' and @Cat = 'Wrn')">
            toggleDisp(<xsl:value-of select="$id"/>Error<xsl:number value="position()"/>)
          </xsl:if>
        </xsl:for-each>
      </xsl:attribute>
      Errors
    </a>
    <a class="Tabs_inactive" style="display:none;background-color:white;">
      <xsl:attribute name="id"><xsl:value-of select="$id"/>Msg</xsl:attribute>
      <xsl:attribute name="onclick">
        toggleActive(<xsl:value-of select="$id"/>Msg)
        <xsl:for-each select="./*">
          <xsl:if test="name() = 'Msg' and @Cat = 'Alw'">
            toggleDisp(<xsl:value-of select="$id"/>Msg<xsl:number value="position()"/>)
          </xsl:if>
        </xsl:for-each>
      </xsl:attribute>
      Msg
    </a>
    <a class="Tabs_inactive" style="display:none;background-color:#CCCCCC;">
      <xsl:attribute name="id"><xsl:value-of select="$id"/>Trace</xsl:attribute>
      <xsl:attribute name="onclick">
        toggleActive(<xsl:value-of select="$id"/>Trace)
        <xsl:for-each select="./*">
          <xsl:if test="name() = 'Trace' or (name() = 'Msg' and @Cat = 'Trc')">
            toggleDisp(<xsl:value-of select="$id"/>Trace<xsl:number value="position()"/>)
          </xsl:if>
        </xsl:for-each>
      </xsl:attribute>
      Trace
    </a>
    <a class="Tabs_inactive" style="display:none;background-color:#CCDDFF;">
      <xsl:attribute name="id"><xsl:value-of select="$id"/>Comment</xsl:attribute>
      <xsl:attribute name="onclick">
        toggleActive(<xsl:value-of select="$id"/>Comment)
        <xsl:for-each select="./*">
          <xsl:if test="name() = 'Comment'">
            toggleDisp(<xsl:value-of select="$id"/>Comment<xsl:number value="position()"/>)
          </xsl:if>
        </xsl:for-each>
      </xsl:attribute>
      Comment
    </a>

    <!-- Add the 'Extra' button only if it is necessary since it should be rare. -->
    <xsl:if test="count(./*[not(name() = 'TestCase') and not(name() = 'Group') and count(.//*[name() = 'Error' or name() = 'Msg' or name() = 'Trace' or name() = 'Comment']) > 0]) > 0">
      <a class="Tabs_inactive" style="display:none;background-color:white;">
      <xsl:attribute name="id"><xsl:value-of select="$id"/>Extra</xsl:attribute>
      <xsl:attribute name="onclick">
        toggleActive(<xsl:value-of select="$id"/>Extra)
        <xsl:for-each select="./*">
          <xsl:if test="not(name() = 'TestCase') and not(name() = 'Group') and count(.//*[name() = 'Error' or name() = 'Msg' or name() = 'Trace' or name() = 'Comment']) > 0">
            toggleDisp(<xsl:value-of select="$id"/>Extra<xsl:number value="position()"/>)
          </xsl:if>
        </xsl:for-each>
      </xsl:attribute>
      Extra
    </a>
      <script>
        toggleDisp(<xsl:value-of select="$id"/>Extra)
      </script>
    </xsl:if>
    <script>
      toggleDisp(<xsl:value-of select="$id"/>Error)
      toggleDisp(<xsl:value-of select="$id"/>Msg)
      toggleDisp(<xsl:value-of select="$id"/>Trace)
      toggleDisp(<xsl:value-of select="$id"/>Comment)
    </script>
  </xsl:template>
  
  <xsl:template name="Results" match="Counter">
    <table width="99%">
      <tr>
        <th colspan="2">Results</th>
      </tr>
      <xsl:for-each select="./Counter">
        <tr style="background-color:#FFFFF6">
          <td style="background-color:#99CCFF;"><xsl:value-of select="substring-before(.,' : ')"/></td>
          <td><xsl:value-of select="substring-before(substring-after(.,' : ['),']')"/></td>
        </tr>
      </xsl:for-each>
    </table>
  </xsl:template>

  <xsl:template name="MetaData" match="MetaData">
    <table width="99%">
      <tr>
        <th colspan="2">Configuration</th>
      </tr>
      <xsl:for-each select="./MetaData/*">
        <tr style="background-color:#FFFFF6">
          <td width="100" style="background-color:#99CCFF;">
            <xsl:value-of select="name()"/>
          </td>
          <td>
            <xsl:value-of select="."/>
          </td>
        </tr>
      </xsl:for-each>
    </table>
  </xsl:template>
  
  <xsl:template name="format-linebreaks">
    <xsl:param name="text"></xsl:param>
    <xsl:variable name="cr" select="'&#xa;'"/>
    <xsl:choose>
      <xsl:when test="contains($text,$cr)">
        <xsl:value-of select="substring-before($text,$cr)"/>
        <br />
        <xsl:call-template name="format-linebreaks">
          <xsl:with-param name="text" select="substring-after($text,$cr)"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="substring-before($text,$cr)"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="linkify" match="a">
    <xsl:param name="line"></xsl:param>
    <xsl:choose>
      <xsl:when test="contains($line, 'file:')">
        <xsl:value-of select="substring-before($line, 'file:')"/>
        <xsl:variable name="remaining"><xsl:value-of select="substring-after($line, 'file:')"/></xsl:variable>
        <a>
          <xsl:attribute name="href"><xsl:value-of select="substring-before($remaining, ' ')"/></xsl:attribute>
          <xsl:value-of select="substring-before($remaining, ' ')"/>
        </a>
        <xsl:call-template name="linkify">
          <xsl:with-param name="line"><xsl:value-of select="substring-after($remaining, ' ')"/></xsl:with-param>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$line"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="time">
    <xsl:param name="timestring"></xsl:param>
    <xsl:choose>
      <xsl:when test="contains($timestring, '.')">
        <!-- Time is a decimal value. Limit the precision. -->
        <xsl:variable name="partialSeconds"
                    select="substring(concat(substring-before(substring-after($timestring,'.'),'s'),'00'),0,3)"/>
        <xsl:value-of select="concat(substring-before($timestring,'.'),'.',$partialSeconds,'s')"/>
      </xsl:when>
      <xsl:otherwise>
        <!-- Time is a reasonable length -->
        <xsl:value-of select="$timestring"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
</xsl:stylesheet>
