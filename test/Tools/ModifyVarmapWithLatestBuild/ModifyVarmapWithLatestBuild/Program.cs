//-----------------------------------------------------------------------
// <copyright file="Program.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-klosli</author>
// <description>Modify varmaps with latest build number of OMI</description>
// <history>6/27/2011 1:59:06 PM: Created</history>
//-----------------------------------------------------------------------

namespace ModifyVarmapWithLatestBuild
{
    using System;
    using System.IO;
    using System.Text.RegularExpressions;

    /// <summary>
    /// Modify test build to latest build in all varmaps
    /// </summary>
    class Program
    {
        static int Main(string[] args)
        {
            if (args.Length == 0 || args.Length > 1)
            {
                Console.WriteLine("Usage: VarmapModifier.exe <folder of varmaps>");
                return 1;
            }

            if (!Directory.Exists(args[0]))
            {
                Console.WriteLine("The specific path does not exist!");
                return 2;
            }

            const string versionFilePath = @"\\scxfiles\team\SCXCM\Test\Automation\OMI\DailyBuilds\BuildSuccess.txt";
            string latestBuildNumber = GetLatestBuildNumber(versionFilePath);

            DirectoryInfo di = new DirectoryInfo(args[0]);
            FileInfo[] fi = di.GetFiles("*.xml");

            foreach (var item in fi)
            {
                ModifyToLatestBuild(item, latestBuildNumber);
                Console.WriteLine("Modification of [{0}] is complete", item.Name);
            }

            return 0;
        }

        /// <summary>
        /// Modify all varmaps with latest build 
        /// </summary>
        /// <param name="fileInfo">FileInfo object for varmap file</param>
        /// <param name="latestBuildNumber">latest build number</param>
        public static void ModifyToLatestBuild(FileInfo fileInfo, string latestBuildNumber)
        {
            string content = string.Empty;

            try
            {
                using (StreamReader sr = fileInfo.OpenText())
                {
                    content = sr.ReadToEnd();
                    content = Regex.Replace(content, "LATESTBUILD",
                    latestBuildNumber, RegexOptions.Multiline);
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Exception occured, failed to modify varmaps to latest build ", ex);
            }

            File.WriteAllText(fileInfo.FullName, content);
        }

        /// <summary>
        /// Get latest build number from version text file
        /// </summary>
        /// <param name="versionFilePath">the path of version file</param>
        /// <returns>latest build number</returns>
        public static string GetLatestBuildNumber(string versionFilePath)
        {
            string buildNumber = string.Empty;

            try
            {
                using (StreamReader sr = new StreamReader(versionFilePath))
                {
                    buildNumber = sr.ReadToEnd();
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Exception occured, failed to get latest build number ", ex);
            }

            return buildNumber;
        }
    }
}
