
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     Files_test.cpp (utilities)
//  Authors:  Chris Lovett
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Files_test.h"

// utilities
#include "StringUtil.h"
#include "Files.h"

// testing
#include "testing.h"

// stl
#include <string>
#include <cstring>
#include <codecvt>
#include <locale>
#include <iostream>

namespace ell
{
    //
    // Tests
    //
    void TestStringf()
    {
        testing::ProcessTest("Stringf with no args", ell::utilities::stringf("test") == "test");
        testing::ProcessTest("Stringf with args", ell::utilities::stringf("test %d is %s", 10, "fun") == "test 10 is fun");
    }

    std::string GetUnicodeTestPath(std::string& basePath)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        std::string testing = ell::utilities::JoinPaths(basePath, "Testing");
        std::string unicode = ell::utilities::JoinPaths(testing, "Unicode");

        // chinese for 'test'
        std::wstring test(L"\u6D4B\u8bd5");
        std::string utf8test = converter.to_bytes(test);

        std::string testdir = ell::utilities::JoinPaths(unicode, utf8test);
        return testdir;
    }

    void TestUnicodePaths(std::string& basePath)
    {
        auto testdir = GetUnicodeTestPath(basePath);
        std::cout << "writing test output to " << testdir << std::endl;

        // bugbug: the rolling build for Linux is giving us EACCESSDENIED on this testdir for some reason...
#ifdef WIN32
        ell::utilities::EnsureDirectoryExists(testdir);
        testing::ProcessTest("Unicode paths", ell::utilities::DirectoryExists(testdir));

        std::string testContent = "this is a test";
        int testContentLength = testContent.size();

        // chinese for 'banana.txt'
        std::wstring banana(L"\u9999\u8549.txt");
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        std::string utf8banana = converter.to_bytes(banana);

        std::string testfile = ell::utilities::JoinPaths(testdir, utf8banana);
        {
            auto outputStream = ell::utilities::OpenOfstream(testfile);
            outputStream.write(testContent.c_str(), testContentLength);
        } 
        {
            auto inputStream = ell::utilities::OpenIfstream(testfile);
            char buffer[100];
            inputStream.read(buffer, testContentLength);
            buffer[testContentLength] = '\0';
            std::string actual(buffer);

            testing::ProcessTest("Unicode file names", actual == testContent);
        }
#endif
    }


} // end namespace
