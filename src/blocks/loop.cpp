#include <blocks/common.h>
#include <types.h>
#include <blocks/loop.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/BasicBlock.h>

void LoopStatement::codegen(CompilerContext &context) const {
  context.enter_visibility_block();
  if (start_) {
    start_->codegen(context);
  }

  auto *currentFunction = context.builder.GetInsertBlock()->getParent();

  auto check_block = llvm::BasicBlock::Create(context.llvm_context, "check_block", currentFunction);
  auto loop_block = llvm::BasicBlock::Create(context.llvm_context, "loop_block", currentFunction);
  auto cont_block = llvm::BasicBlock::Create(context.llvm_context, "afterloop_block", currentFunction);
  context.builder.CreateBr(check_block);
  context.builder.SetInsertPoint(check_block);
  
  auto condition = boolify(context, condition_->codegen(context));
  context.builder.CreateCondBr(condition.val, loop_block, cont_block);

  // Emit loop content 
  context.builder.SetInsertPoint(loop_block);
  for (auto &st: content_) {
    st->codegen(context);
  }
  if (step_) {
    step_->codegen(context);
  }
  context.builder.CreateBr(check_block);

  // Exit from loop
  context.builder.SetInsertPoint(cont_block);
  context.exit_visibility_block();
}