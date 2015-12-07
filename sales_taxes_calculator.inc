<?php

/**
 * @file
 * Contains sales_taxes_shopping_basket
 */

/**
 * Calculate sales taxes
 */
class sales_taxes_calculator {

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
  public static $EXEMPT_PRODUCTS = ['book', 'food', 'medical product', 'box of chocolates', 'chocolate bar'];

  /**
   * Get the basic sales tax
   *
   * The basic sales tax is 0 for exempt products and self::BASIC_SALES_TAX for the rest.
   *
   * @return float
   */
  public static function get_basic_sales_tax($product) {
    return in_array($product->name, self::$EXEMPT_PRODUCTS) ? 0 : $product->price * self::BASIC_SALES_TAX;
  }

  /**
   * Get the import duty
   *
   * The import duty tax only applies to impoted products and its amount is self::IMPORT_DUTY
   *
   * @return float
   */
  public static function get_import_duty($product) {
    return $product->imported ? $product->price * self::IMPORT_DUTY : 0;
  }

  /**
   * Get the total sales tax
   *
   * The total sales tax is the sum of the individual sales taxes rounded to the nearest 0.05
   *
   * @return float
   */
  public static function get_total_sales_tax($product) {
    $total_tax = self::get_basic_sales_tax($product) + self::get_import_duty($product);
    return round($total_tax * 2, 1) / 2;
  }
}
