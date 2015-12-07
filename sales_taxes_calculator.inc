<?php namespace Zendka\sales_taxes;

/**
 * the basic sales tax
 * it applies to all goods that are not exempt
 */
const BASIC_SALES_TAX = .10; // 10%

/**
 * the import duty sales tax
 * it only applies to imported goods.
 */
const IMPORT_DUTY = .05; // 5%

/**
 * products exempt from the basic sales tax
 * @var [string]
 */
const EXEMPT_PRODUCTS = ['book', 'food', 'medical product', 'box of chocolates', 'chocolate bar'];

/**
 * Get the basic sales tax
 *
 * The basic sales tax is 0 for exempt products and BASIC_SALES_TAX for the rest.
 *
 * @return float
 */
function get_basic_sales_tax($product) {
  return in_array($product->name, EXEMPT_PRODUCTS) ? 0 : $product->price * BASIC_SALES_TAX;
}

/**
 * Get the import duty
 *
 * The import duty tax only applies to impoted products and its amount is IMPORT_DUTY
 *
 * @return float
 */
function get_import_duty($product) {
  return $product->imported ? $product->price * IMPORT_DUTY : 0;
}

/**
 * Get the total sales tax
 *
 * The total sales tax is the sum of the individual sales taxes rounded to the nearest 0.05
 *
 * @return float
 */
function get_total_sales_tax($product) {
  $total_tax = get_basic_sales_tax($product) + get_import_duty($product);
  return round($total_tax * 2, 1) / 2;
}
