#include "types.h"
#include <blocks/if.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/BasicBlock.h>

void IfStatement::codegen(CompilerContext &context) const {
  auto any_cond_val = condition_->codegen(context);
  auto cond_val = cast(context, any_cond_val, ValType{ValType::Kind::Int, 64});

  auto *currentFunction = context.builder.GetInsertBlock()->getParent();

  auto zero = llvm::ConstantInt::get(cond_val.type.llvm_type(context.llvm_context), llvm::APInt(64, 0));

  auto condition = context.builder.CreateICmpNE(cond_val.val, zero);

  auto if_block = llvm::BasicBlock::Create(context.llvm_context, "if_block", currentFunction);
  auto else_block = llvm::BasicBlock::Create(context.llvm_context, "else_block", currentFunction);
  auto cont_block = llvm::BasicBlock::Create(context.llvm_context, "ifcont_block", currentFunction);

  context.builder.CreateCondBr(condition, if_block, else_block);
  
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