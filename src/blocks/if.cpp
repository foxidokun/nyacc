#include "blocks/common.h"
#include "types.h"
#include <blocks/if.h>
#include <fmt/base.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/Support/raw_ostream.h>

void IfStatement::codegen(CompilerContext &context) const {
  // Create blocks
  auto *currentFunction = context.builder.GetInsertBlock()->getParent();
  auto if_block = llvm::BasicBlock::Create(context.llvm_context, "if_block", currentFunction);
  auto else_block = llvm::BasicBlock::Create(context.llvm_context, "else_block", currentFunction);
  auto cont_block = llvm::BasicBlock::Create(context.llvm_context, "ifcont_block", currentFunction);

  // Calculate predicate and create jumps
  auto condition = boolify(context, condition_->codegen(context));
  context.builder.CreateCondBr(condition.val, if_block, else_block);
  
  // Write IF block
  context.enter_visibility_block();
  context.builder.SetInsertPoint(if_block);
  for (auto &st: if_content_) {
    st->codegen(context);
  }
  context.builder.CreateBr(cont_block);
  context.exit_visibility_block();

  // Write ELSE block
  context.enter_visibility_block();
  context.builder.SetInsertPoint(else_block);
  for (auto &st: else_content_) {
    st->codegen(context);
  }
  context.builder.CreateBr(cont_block);
  context.exit_visibility_block();

  // Switch to cont block
  context.builder.SetInsertPoint(cont_block);
}