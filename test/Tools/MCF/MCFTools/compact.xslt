<?xml version="1.0" encoding="UTF-8" ?>
<!-- This XSL file is used to compact an HTML file by removing scripts and invisible elements -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:msxsl="urn:schemas-microsoft-com:xslt"
                xmlns:user="http://mycompany.com/mynamespace"
                version="1.0">
  <xsl:output method="xml" indent="yes"/>
  
  <xsl:template name="child" match="*">
    <xsl:if test="name() != 'script'">
      <xsl:if test="not(@extra) or not(contains(@extra, 'true'))">
        <xsl:if test="not(@style) or not(contains(@style, 'display:none'))">
          <xsl:copy>
            <xsl:copy-of select="@*[not(name() = 'onclick')]" />
            <xsl:apply-templates />
          </xsl:copy>
        </xsl:if>
      </xsl:if>
    </xsl:if>
  </xsl:template>
  
</xsl:stylesheet>
