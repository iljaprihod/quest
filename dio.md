# CLOTHES SHOP
```mermaid
---
title: Animal example
---
classDiagram
 User <|--Shop
 clothes <|--Shop
 class User{
    string login
    string passwd
    string name
    string adress
 }
 class clothes{
    string color
    string brand
    string type
    string size
    int price
 }
 class cart{
   int quant
   string clothes
   int price
 }
 hoodie<|-- clothes
  t-shirt<|-- clothes
   shirts<|-- clothes
    pants<|-- clothes
     socks<|-- clothes
      underwear<|-- clothes
      hats<|-- clothes
cart <|-- User
 cart<|-- hoodie
  cart<|-- t-shirt
   cart<|-- shirts
    cart<|-- pants
     cart<|-- socks
      cart<|-- clothes
      cart<|-- hats


class checkout{
   "inherit adress,\ncard from user, all other from cart"
}
checkout <| -- cart