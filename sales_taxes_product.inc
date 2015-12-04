<?php

/**
 * @file
 * Contains sales_taxes_product
 */

/**
 * Handles product sales tax
 */
class sales_taxes_product {

  /**
   * the basic sales tax
   * it only applies to all goods that are not exempt
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
   * the product name
   * @var string
   */
  public $name;

  /**
   * the pre sales tax price
   * @var float
   */
  public $price;

  /**
   * the import status of the product: true if imported, false otherwise
   * @var bool
   */
  public $imported;

  /**
   * the number of items
   * @var int
   */
  public $quantity;

  /**
   * Constructor
   *
   * @param string $product the product name
   * @param float $price the pre sales tax price
   * @param bool $imported the import status of the product: true if imported, false otherwise
   * @param int $quantity the number of items
   */
  public function __construct($product_name, $price, $imported = false, $quantity = 1) {
    $this->name = $product_name;
    $this->price = $price;
    $this->imported = $imported;
    $this->quantity = $quantity;
  }

  /**
   * Get the basic sales tax
   *
   * The basic sales tax is 0 for exempt products and self::BASIC_SALES_TAX for the rest.
   *
   * @return float
   */
  public function get_basic_sales_tax() {
    return in_array($this->name, self::$EXEMPT_PRODUCTS) ? 0 : $this->price * self::BASIC_SALES_TAX;
  }

  /**
   * Get the import duty
   *
   * The import duty tax only applies to impoted products and its amount is self::IMPORT_DUTY
   *
   * @return float
   */
  public function get_import_duty() {
    return $this->imported ? $this->price * self::IMPORT_DUTY : 0;
  }

  /**
   * Get the total sales tax
   *
   * @return float
   */
  public function get_total_sales_tax() {
    $total_tax = $this->get_basic_sales_tax() + $this->get_import_duty();
    return $this->get_rounded_up_to_0_05($total_tax);
  }

  /**
   * Get the rounded up value to the nearest 0.05
   *
   * @param  float $n
   * @return float
   */
  private function get_rounded_up_to_0_05($n) {
    return round($n * 2, 1) / 2;
  }
}
