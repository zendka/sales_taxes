<?php

/**
 * @file
 * Contains sales_taxes_shopping_basket
 */

require_once('sales_taxes_calculator.inc');

/**
 * Shopping Basket with products
 */
class sales_taxes_shopping_basket {

  /**
   * the list of products in the shopping basket
   * @var [product]
   */
  private $products = [];

  /**
   * the quantity of each product in the shopping cart
   * @var int
   */
  private $quantities = [];

  /**
   * Constructor
   *
   * @param [product] $products the list of products in the shopping basket
   * @param [int] $quantities the quantity of each product in the shopping cart
   */
  public function __construct($products, $quantities) {
    $this->products = $products;
    $this->quantities = $quantities; // @todo what if the size is not the same?
  }

  /**
   * Calculate the price for each product type (product price * quantity)
   *
   * @return [float]
   */
  private function get_prices() {
    $prices = [];
    for ($i=0; $i<sizeof($this->products); $i++) {
      $prices[$i] = $this->products[$i]->price * $this->quantities[$i];
    }

    return $prices;
  }

  /**
   * Calculate the sales tax for each product type (product sales tax * quantity)
   *
   * @return [float]
   */
  private function get_sales_taxes() {
    $sales_taxes = [];
    for ($i=0; $i<sizeof($this->products); $i++) {
      $sales_taxes[$i] = \Zendka\sales_taxes\get_total_sales_tax($this->products[$i]) * $this->quantities[$i];
    }

    return $sales_taxes;
  }

  /**
   * Displays the receipt for the products in the shopping basket
   *
   * It has the following format:
   * 1 imported box of chocolates: 10.50 1 imported bottle of perfume: 54.65 Sales Taxes: 7.65 Total: 65.15
   *
   * @return string the receipt in the specific format
   */
  public function get_receipt() {
    $prices = $this->get_prices();
    $sales_taxes = $this->get_sales_taxes();

    $receipt = '';
    for ($i=0; $i<sizeof($this->products); $i++) {
      $receipt .= t("@quantity @imported@product_name: @total_price ", array(
        '@quantity' => $this->quantities[$i],
        '@imported' => $this->products[$i]->imported ? 'imported ': '',
        '@product_name' => $this->products[$i]->name,
        '@total_price' => number_format($prices[$i] + $sales_taxes[$i], 2),
      ));
    }

    $receipt .= 'Sales taxes: ' . number_format(array_sum($sales_taxes), 2);
    $receipt .= ' Total: ' . number_format(array_sum($prices) + array_sum($sales_taxes), 2);

    return $receipt;
  }
}
