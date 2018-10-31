#ifndef __KCC_AST_H
#define __KCC_AST_H

// https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm

struct kcc_ast_s {
  union {
    kcc_trans_t *trans;
  }data;
};

struct kcc_trans_s {
  kcc_exrn_decl_s decls[];
};

struct kcc_exrn_decl_s {
  int typ;
  union {
    kcc_function_def_t *func_def;
    kcc_decl_t *decl;
  data;
};

struct kcc_function_def_s {
  kcc_decl_sepcifier_t *decls_specs;
  kcc_declarator_s *declear;
  kcc_compound_stmt_t *compound_stmt;
};

struct kcc_decl_specifier_s {
  int typ;
  union {
    kcc_storage_class_spec_t *storage_class_spec;
    kcc_type_spec_t *type_spec;
    kcc_type_qualifier_t *type_qualifier;
  }data;

};

struct kcc_storage_class_spec_s {
  int typ;
};

struct kcc_type_spec_s {
  int typ;
};

struct kcc_struct_or_union_spec_s {
  int typ;
  union {
    struct {
    }named_struct_def;
    struct{
      kcc_struct_declarator_s
    }anon_structs_def;
    struct {
    }anon_struct_def
  }data;
};

struct kcc_struct_or_union_s {
};

struct kcc_spec_qualifier_s {
};

struct kcc_struct_decl_list_s{
};

struct kcc_struct_declarator_s {
};

struct kcc_declarator_s {
};

struct kcc_pointer_s {
};

struct kcc_type_qualifier_s {
};

struct kcc_direct_dclarator_s {
};

struct kcc_conditional_expr_s {
};

struct kcc_logical_or_expr_s {
};

struct kcc_logical_and_expr_s {
};

struct kcc_inclusive_or_expr_s {
};

struct kcc_and_expr_s {
};

struct kcc_equality_expr_s {
};

struct kcc_relational_expr_s {
};

struct kcc_shift_expr_s {
};

struct kcc_additive_expr_s {
};

struct kcc_muti_expr_s {
};

struct kcc_cast_expr_s {
};

struct kcc_unary_expr_s {
};

struct kcc_pstfix_expr_s {
};

struct kcc_primary_expr_s {
};

struct kcc_constant_expr_s {
};

struct kcc_expr_s {
};

struct kcc_assign_expr_s {
};

struct kcc_assign_op_s {
};

struct kcc_unary_op_s {
};

struct kcc_typ_naem_s {
};

struct kcc_param_type_list_s {
};

struct kcc_param_list_s {
};

struct kcc_param_decl_s {
};

struct kcc_abst_decl_s {
};

struct kcc_direct_abst_decl_s {
};

struct kcc_enum_spec_s {
};

struct kcc_spec_list_s {
};

struct kcc_enum_s {
};

struct kcc_typedef_name_s {
};

struct kcc_decl_s {
};

struct kcc_init_decl_s {
};

struct kcc_initializer_s {
};

struct kcc_initializer_list_s {
};

struct kcc_compound_stmt_s {
};

struct kcc_stmt_s {
};

struct kcc_labled_stmt_s {
};

struct kcc_expr_stmt_s {
};

struct kcc_selection_stmt_s {
};

struct kcc_iteration_stmt_s {
};

struct kcc_jump_stmt_s {
};

typedef struct kcc_ast_s kcc_ast_t;
typedef struct kcc_trans_s  kcc_trans_t;
typedef struct kcc_exrn_decl_s  kcc_exrn_decl_t;
typedef struct kcc_function_def_s kcc_function_def_t;
typedef struct kcc_decl_specifier_s kcc_decl_sepcifier_t;
typedef struct kcc_storage_class_spec_s kcc_storage_class_spec_t;
typedef struct kcc_type_spec_s kcc_type_spec_t;
typedef struct kcc_struct_or_union_spec_s kcc_struct_or_union_spec_t;
typedef struct kcc_struct_or_union_s kcc_struct_or_union_t;
typedef struct kcc_spec_qualifier_s kcc_spec_qualifier_t;
typedef struct kcc_struct_decl_list_s kcc_struct_decl_list_t;
typedef struct kcc_struct_declarator_s kcc_struct_declarator_t;
typedef struct kcc_declarator_s kcc_declarator_t;
typedef struct kcc_pointer_s kcc_pointer_t;
typedef struct kcc_type_qualifier_s kcc_type_qualifier_t;
typedef struct kcc_direct_dclarator_s kcc_direct_dclarator_t;
typedef struct kcc_conditional_expr_s kcc_conditional_expr_t;
typedef struct kcc_logical_or_expr_s kcc_logical_or_expr_t;
typedef struct kcc_logical_and_expr_s kcc_logical_and_expr_t;
typedef struct kcc_inclusive_or_expr_s kcc_inclusive_or_expr_t;
typedef struct kcc_and_expr_s kcc_and_expr_t;
typedef struct kcc_equality_expr_s kcc_equality_expr_t;
typedef struct kcc_relational_expr_s kcc_relational_expr_t;
typedef struct kcc_shift_expr_s kcc_shift_expr_t;
typedef struct kcc_additive_expr_s kcc_additive_expr_t;
typedef struct kcc_muti_expr_s kcc_muti_expr_t;
typedef struct kcc_cast_expr_s kcc_cast_expr_t;
typedef struct kcc_unary_expr_s kcc_unary_expr_t;
typedef struct kcc_pstfix_expr_s kcc_pstfix_expr_t;
typedef struct kcc_primary_expr_s kcc_primary_expr_t;
typedef struct kcc_constant_expr_s kcc_constant_expr_t;
typedef struct kcc_expr_s kcc_expr_t;
typedef struct kcc_assign_expr_s kcc_assign_expr_t;
typedef struct kcc_assign_op_s kcc_assign_op_t;
typedef struct kcc_unary_op_s kcc_unary_op_t;
typedef struct kcc_typ_naem_s kcc_typ_naem_t;
typedef struct kcc_param_type_list_s kcc_param_type_list_t;
typedef struct kcc_param_list_s kcc_param_list_t;
typedef struct kcc_param_decl_s kcc_param_decl_t;
typedef struct kcc_abst_decl_s kcc_abst_decl_t;
typedef struct kcc_direct_abst_decl_s kcc_direct_abst_decl_t;
typedef struct kcc_enum_spec_s kcc_enum_spec_t;
typedef struct kkcc_spec_list_s _cc_spec_list_t;
typedef struct kcc_enum_s kcc_enum_t;
typedef struct kcc_typedef_name_s kcc_typedef_name_t;
typedef struct kcc_decl_s kcc_decl_t;
typedef struct kcc_init_decl_s kcc_init_decl_t;
typedef struct kcc_initializer_s kcc_initializer_t;
typedef struct kcc_initializer_list_s kcc_initializer_list_t;
typedef struct kcc_compound_stmt_s kcc_compound_stmt_t;
typedef struct kcc_stmt_s kcc_stmt_t;
typedef struct kcc_labled_stmt_s kcc_labled_stmt_t;
typedef struct kcc_expr_stmt_s kcc_expr_stmt_t;
typedef struct kcc_selection_stmt_s kcc_selection_stmt_t;
typedef struct kcc_iteration_stmt_s kcc_iteration_stmt_t;
typedef struct kcc_jump_stmt_s kcc_jump_stmt_t;

int kcc_ast_print(kcc_ast_t *);
#endif
