#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <stdexcept>
#include <tr1/memory>

//////////////////
#include "parser/single_char_parser.hpp"
#include "parser/none_or_more_parser.hpp"
#include "parser/alternative_parser.hpp"
#include "parser/ast_parse.hpp"
/////////////////////

#include "grammar.hpp"
#include "utils.hpp"
#include "parse_tree/parse_tree.hpp"

#include "parse_tree/dump_visitor.hpp"

int main() {
  std::string const s(readEntireFile("1.dat"));
  std::cout << "code: '" << s << "'" << std::endl;
  char const* const str = s.c_str();

  typedef AstParseInfo<char const*> parse_info_t;
  parse_info_t const tpi =
    ast_parse(str, str+strlen(str), MyGrammar(),
              *(ch_p(' ') | ch_p('\t') | ch_p('\r') | ch_p('\n')));
  
  using namespace PT;

  ASTToPTConverterFactory<typename parse_info_t::node_t, decltype(MyGrammar())> factory;
  ProgramNode const program(factory.buildProgramTree(tpi.nodes[0]));

  Utils::dumpProgramNode(program);

  //program.dump();

  /*ExecutorContext context;
  typedef test::ExpressionTypeAnalyzer<parse_info_t::node_t, MyGrammar, ExecutorContext> analyzer_t;
  analyzer_t analyzer(context);

  try {
    Type const& type(analyzer.getExpressionType(tpi.nodes[0]));
    std::cout << "type is " << type.getTypeName() << std::endl;
  } catch(IErrorContext const& errorContext) {
    errorContext.dump(0);
  } catch(IError const& error) {
    error.dump(0);
  }*/

  return 0;
}
