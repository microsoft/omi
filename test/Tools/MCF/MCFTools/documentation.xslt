<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:msxsl="urn:schemas-microsoft-com:xslt"
                xmlns:user="http://mycompany.com/mynamespace"
                version="1.0">
  <xsl:output method="xml"/>

  <xsl:template name="root" match="/">
    <html>
      <head>
        <title>Test Result Report</title>
      </head>
      <body>
        <table width="99%" rules="groups">
          <xsl:for-each select="//members/member[contains(@name, 'T:')]">
              <xsl:call-template name="WriteClass">
              </xsl:call-template>
          </xsl:for-each>
        </table>
      </body>
    </html>
  </xsl:template>

  <xsl:template name="WriteClass" match="WriteClass">
    <xsl:variable name="class">M:<xsl:value-of select="substring-after(@name, 'T:')"/>.</xsl:variable>
    <thead>
    <tr>
      <td colspan="3">
        <b>
          <xsl:value-of select="substring-after(@name, 'T:')"/>
        </b>
      </td>
    </tr>
    <tr>
      <td colspan="3">
          <xsl:copy-of select="summary"/>
      </td>
    </tr>
    </thead>
          <xsl:for-each select="//members/member[contains(@name, $class)]">
            <xsl:sort select="@name"/>
                <xsl:call-template name="WriteClassMethod">
                  <xsl:with-param name="prefix" select="$class"/>
                </xsl:call-template>
          </xsl:for-each>
  </xsl:template>

  <xsl:template name="WriteClassMethod">
    <xsl:param name="prefix"></xsl:param>
    <tbody>
      <tr>
        <td width="4%"/>
        <td colspan="2">
          <b>
            <xsl:value-of select="substring-after(@name, $prefix)"/>
            <xsl:if test="not(contains(substring-after(@name, $prefix), '('))">
              <xsl:value-of select="'( )'"/>
            </xsl:if>
          </b>
        </td>
      </tr>
      <tr>
        <td/>
        <td colspan="2">
            <xsl:copy-of select="summary"/>
        </td>
      </tr>
        <xsl:for-each select="param">
          <tr>
            <td/>
            <td>
              <font color="blue">
                <xsl:value-of select="@name"/>
              </font>
            </td>
            <xsl:choose>
              <xsl:when test="../see and string-length(.) = 0">
                <xsl:variable name="ref" select="../see/@cref"/>
                <xsl:variable name="param" select="@name"/>
                <td>
                  <xsl:value-of select="//members/member[@name=$ref]/param[@name=$param]"/>
                </td>
              </xsl:when>
              <xsl:otherwise>
                <td>
                  <xsl:value-of select ="."/>
                </td>
              </xsl:otherwise>
            </xsl:choose>
          </tr>
        </xsl:for-each>
    </tbody>
  </xsl:template>
    
</xsl:stylesheet>
