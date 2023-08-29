#ifndef __EVAR_H
#define __EVAR_H

#include <string>
#include "trim.h"

class evar
{
    public:
        evar(const std::string s) : mValid(false), mOutput(false)
        {
           size_t found = s.find("=");
            if (found == std::string::npos || found==0)
                mValid=false;
            else
            {
                mKey=s.substr(0,found);
                size_t lastchar=s.length()-1;
                if (found<lastchar)
                    mValue=s.substr(found+1,lastchar-found);

                trim(mKey);
                trim(mValue);
                mValid=true;
            }
        }

        bool valid() const {return mValid;}
        bool output() const {return mOutput;}
        std::string key() const {return mKey;}
        std::string value() const {return mValue;}
        std::string str() const {return mKey+"="+mValue;}
        bool samekey(evar const & other) const
        {
            return (key().compare(other.key()) == 0);
        }

        void setOutput(bool v) {mOutput=v;}

    private:
        bool mValid,mOutput;
        std::string mKey,mValue;
};

#endif
