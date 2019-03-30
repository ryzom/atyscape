/** 
 * AtysScape - Utils
 * 2008-05-08 - Ulukyn
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

#ifndef _LG_UTILS_H_
#define _LG_UTILS_H_

#include <string>
#include <vector>
#include <sstream>

using namespace std;

void tokenizer(const string& str, vector<string>& tokens, const string& delimiters = " ");
float string2float(const string &value);
int string2int(const string &value);

#endif
