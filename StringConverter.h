/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef __StringConverter_H__
#define __StringConverter_H__


class StringConverter
{
public:

    /** Converts a Real to a String. */
	static std::string toString(float val, unsigned short precision = 6, 
        unsigned short width = 0, char fill = ' ', 
        std::ios::fmtflags flags = std::ios::fmtflags(0) );
    /** Converts an int to a String. */
    static std::string toString(int val, unsigned short width = 0, 
        char fill = ' ', 
        std::ios::fmtflags flags = std::ios::fmtflags(0) );
    /** Converts an unsigned int to a String. */
    static std::string toString(unsigned int val, 
        unsigned short width = 0, char fill = ' ', 
        std::ios::fmtflags flags = std::ios::fmtflags(0) );
    
    /** Converts an unsigned long to a String. */
    static std::string toString(unsigned long val, 
        unsigned short width = 0, char fill = ' ', 
        std::ios::fmtflags flags = std::ios::fmtflags(0) );
    /** Converts a long to a String. */
    static std::string toString(long val, 
        unsigned short width = 0, char fill = ' ', 
        std::ios::fmtflags flags = std::ios::fmtflags(0) );

    
    /** Converts a String to a Real. 
    @returns
        0.0 if the value could not be parsed, otherwise the Real version of the String.
    */
    static float parseFloat(const std::string& val);
    
    /** Converts a String to a whole number. 
    @returns
        0.0 if the value could not be parsed, otherwise the numeric version of the String.
    */
    static int parseInt(const std::string& val);
    /** Converts a String to a whole number. 
    @returns
        0.0 if the value could not be parsed, otherwise the numeric version of the String.
    */
    static unsigned int parseUnsignedInt(const std::string& val);
    /** Converts a String to a whole number. 
    @returns
        0.0 if the value could not be parsed, otherwise the numeric version of the String.
    */
    static long parseLong(const std::string& val);
    /** Converts a String to a whole number. 
    @returns
        0.0 if the value could not be parsed, otherwise the numeric version of the String.
    */
    static unsigned long parseUnsignedLong(const std::string& val);
    
};




#endif

