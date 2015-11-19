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
   * the product name
   * @var string
   */
  private $name;

  /**
   * the pre sales tax price
   * @var float
   */
  private $price;

  /**
   * the import status of the product: true if imported, false otherwise
   * @var bool
   */
  private $imported;

  /**
   * the number of items
   * @var int
   */
  private $quantity;

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
   * @return float the resulting basic sales tax
   */
  public function get_basic_sales_tax() {
    $exempt_products = ['book', 'food', 'medical product', 'box of chocolates', 'chocolate bar'];

    if (in_array($this->name, $exempt_products)) {
      $tax = 0;
    }
    else {
      // Tax is 10%
      $tax = $this->price * 0.10;
    }

    return $tax;
  }

  /**
   * Get the import duty
   *
   * @return float the resulting import duty
   */
  public function get_import_duty() {
    if ($this->imported) {
      // Tax is 5%
      $tax = $this->price * .05;
    }
    else {
      $tax = 0;
    }

    return $tax;
  }

  /**
   * Get the total sales tax
   *
   * @return float the resulting sales tax
   */
  public function get_total_sales_tax() {
    $total_tax = $this->get_basic_sales_tax() + $this->get_import_duty();
    return $this->get_rounded_up_to_0_05($total_tax);
  }

  /**
   * Get the rounded up value to the nearest 0.05
   *
   * @param  float $n
   * @return string the string representing the number with two decimal precision
   */
  private function get_rounded_up_to_0_05($n) {
    if (fmod($n, .05) == 0) {
      return $n;
    }
    else {
      return sprintf("%.2f", $n + (.05- fmod($n, .05)));
    }
  }
}
