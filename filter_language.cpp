#include "prec.h"
#include "filter_language.h"
#include "sentence.h"

NAMESPACE_START

// __________________________________________________________________________ //

int FilterLanguage::filter( const sentence & _sentence )
{
    int ret = SUCCESS;

    if( !m_countryCode.empty() )
    {
        if( m_countryCode != _sentence.getCountryCode() )
            ret = DOES_NOT_MATCH;
    }
    else
        ret = INTERNAL_ERROR;

    return ret;
}

NAMESPACE_END
