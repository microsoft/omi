
@{
    GUID = '3af1699d-cc54-4e54-81cf-28d2df5cce0a'
    Author="Demo"
    CompanyName="Demo"
    Copyright="© Microsoft. All rights reserved."
    HelpInfoUri="http://demo/uri"
    NestedModules = @('CIM_ComputerSystem.cdxml','CIM_EthernetPort.cdxml','Cim_VlanEndPoint')
    ModuleVersion = '1.0.0.0'
    AliasesToExport = @()
    FunctionsToExport = @('Get-SwitchConfiguration','Get-SwitchEthernetPort','Get-SwitchVLanEndPoint')
    PowerShellVersion = '3.0'
    TypesToProcess = @('CIM_EthernetPort.types.ps1xml', 'CIM_ComputerSystem.types.ps1xml', 'CIM_VlanEndpoint.types.ps1xml')
    FormatsToProcess = @('CIM_EthernetPort.format.ps1xml', 'CIM_ComputerSystem.format.ps1xml', 'CIM_VlanEndpoint.format.ps1xml')
}
