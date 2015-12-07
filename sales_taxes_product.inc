<?php

/**
 * @file
 * Contains sales_taxes_product
 */

/**
 * Product
 */
class sales_taxes_product {

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
  }
}
