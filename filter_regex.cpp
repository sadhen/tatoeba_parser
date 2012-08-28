#include "prec.h"
#include "filter_regex.h"
#include "sentence.h"

NAMESPACE_START

FilterRegex::FilterRegex( )
    :m_regex( nullptr )
    ,m_status( U_ZERO_ERROR )
{
}

// __________________________________________________________________________ //

int FilterRegex::filter( const sentence & _candidate )
{
    int ret = SUCCESS;

    // did memory allocation succeed
    if( m_regex )
    {
        // did computation of the regular expression work
        if( U_FAILURE( m_status ) )
            ret = INVALID_ARG;
    }
    else
        ret = OUT_OF_MEMORY;

    // now try and match it with the sentence
    if( ret == SUCCESS )
    {
        m_regex->reset( _candidate.text() );

        if( !m_regex->matches( m_status ) )
            ret = DOES_NOT_MATCH;
    }

    return ret;
}

// __________________________________________________________________________ //

int FilterRegex::computeRegex( const std::string & _regex )
{
    ASSERT_EQ( m_regex, nullptr );
    //allocate and compute the regex
    m_regex = new RegexMatcher( _regex.c_str(), 0, m_status );

    return SUCCESS;
}

// __________________________________________________________________________ //

FilterRegex::~FilterRegex()
{
    delete m_regex;
}

// __________________________________________________________________________ //

int FilterRegex::setRegex( const std::string & _regex )
{
    computeRegex( _regex );
    ASSERT( m_regex != nullptr );
    
    return SUCCESS;
}
NAMESPACE_END
