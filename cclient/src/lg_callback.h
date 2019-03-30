/** 
 * AtysScape - Callback
 * 2008-05-15 - Ulukyn
 * 
 * Atyscape is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software: if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _LG_CALLBACK_H_
#define _LG_CALLBACK_H_

#include <string>

using namespace std;

namespace LG
{

class CCallbackObj
{
public:
    virtual ~CCallbackObj() {};
    virtual bool operator()(const string &winName) = 0;
};


template<typename T>
class TCallbackObj : public CCallbackObj
{
public:
	typedef bool(T::*TCallbackFunc)(const string&);

    TCallbackObj(TCallbackFunc func, T* obj) : _Function(func), _Object(obj)
    {
	}

    virtual bool operator()(const string &winName)
    {
        return (_Object->*_Function)(winName);
    }

private:
    TCallbackFunc _Function;
    T* _Object;
};


class CCallback
{
public:
 
    CCallback();

    template<typename T>
    CCallback(bool(T::*function)(const string&), T* obj) : callback(new TCallbackObj<T>(function, obj))
    {}

    ~CCallback();

	bool operator()(const string &winName) const
    {
        return (*callback)(winName);
    }

    void remove();


private:
    CCallbackObj* callback;
};

}

#endif
