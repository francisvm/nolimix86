#include <ast/pretty-printer.hh>

#include <algorithm>

// Sorry :(
#define print_instr(instr)                                                     \
  void                                                                         \
  pretty_printer::operator()(const instr &e)                                   \
  {                                                                            \
    ostream_ << #instr;                                                        \
    if (e.size() > 0)                                                          \
    {                                                                          \
      ostream_ << ' ';                                                         \
      std::for_each(e.begin(), std::prev(e.end()), [&](const auto &op)         \
      {                                                                        \
        (*this)(op);                                                           \
        ostream_ << ", ";                                                      \
      });                                                                      \
                                                                               \
      (*this)(*std::prev(e.end()));                                            \
    }                                                                          \
    ostream_ << '\n';                                                          \
  }

namespace nolimix86
{

  namespace ast
  {

    pretty_printer::~pretty_printer() = default;

    pretty_printer::pretty_printer(llvm::raw_ostream& ostream)
      : ostream_{ostream}
    {
      ostream_ << "  .text\n";
    }

    void
    pretty_printer::operator()(const operand& e)
    {
      e.dump(ostream_);
    }

    void
    pretty_printer::operator()(const basic_block& e)
    {
      ostream_ << e.label_get() << ":\n";
      super_type::operator()(e);
    }

    print_instr(add)
    print_instr(call)
    print_instr(cmp)
    print_instr(idiv)
    print_instr(imul)
    print_instr(ja)
    print_instr(jae)
    print_instr(jb)
    print_instr(jbe)
    print_instr(je)
    print_instr(jg)
    print_instr(jge)
    print_instr(jl)
    print_instr(jle)
    print_instr(jmp)
    print_instr(jne)
    print_instr(js)
    print_instr(lea)
    print_instr(leave)
    print_instr(mov)
    print_instr(neg)
    print_instr(pop)
    print_instr(push)
    print_instr(ret)
    print_instr(sal)
    print_instr(sar)
    print_instr(sete)
    print_instr(sub)
    print_instr(test)
#undef print_instr

  } // namespace ast

} // namespace nolimix86
