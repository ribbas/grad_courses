#include <string>
#include <fstream>
#include <ios>
#include <boost/regex.hpp>

class XMLTokenizer
{
private:
	std::fstream		file;
	std::string		line;
	int			line_number;
	int			index;
	bool			inside_tag;
	bool			pending_attribute_value;
	bool			tag_found;

	static const char *	PROLOG_START;
	static const char *	PROLOG_IDENTIFIER;
	static const char *	ATTRIBUTE_VALUE;
	static const char *	PROLOG_END;
	static const char *	TAG_START;
	static const char *	ELEMENT;
	static const char *	ATTRIBUTE;
	static const char *	NULL_TAG_END;
	static const char *	TAG_CLOSE_START;
	static const char *	VALUE;
	static const char *	TAG_END;
	static const char *	SPACE_TO_EOL;

	boost::regex	prolog_start;
	boost::regex	prolog_identifier;
	boost::regex	attribute_value;
	boost::regex	prolog_end;
	boost::regex	tag_start;
	boost::regex	element;
	boost::regex	attribute;
	boost::regex	null_tag_end;
	boost::regex	tag_close_start;
	boost::regex	value;
	boost::regex	tag_end;
	boost::regex	space_to_eol;

	virtual void		update_matchers(const boost::ssub_match &, const boost::ssub_match & suffix);
public:
	class XMLToken
	{
	public:
		enum TokenTypes
		{
			NULL_TOKEN		=  0,
			PROLOG_START		=  1,
			PROLOG_IDENTIFIER	=  2,
			ATTRIBUTE_VALUE		=  3,
			PROLOG_END		=  4,
			TAG_START		=  5,
			ELEMENT			=  6,
			ATTRIBUTE		=  7,
			NULL_TAG_END		=  8,
			TAG_CLOSE_START		=  9,
			VALUE			= 10,
			TAG_END			= 11
		};
	private:
		std::string	token;
		TokenTypes	token_type;
	public:
		XMLToken(const std::string & t, TokenTypes tt);

		virtual ~XMLToken() {}

		virtual const std::string &	getToken(void)		{ return token; }
		virtual TokenTypes		getTokenType(void)	{ return token_type; }
		virtual const char *		toString(void);
	};

	XMLTokenizer(const std::string & filename);
	~XMLTokenizer() {}

	virtual int		getLineNumber(void)	{ return line_number; }
	virtual int		getLineCharacter(void)	{ return index; }
	virtual XMLToken *	getNextToken(void);
};
