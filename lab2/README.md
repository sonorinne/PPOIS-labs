# Пиццерия

Консольное приложение на C++17 для работы с заказами пиццерии. В модели есть склад ингредиентов, рецепты, меню, оплата, кухня, упаковка и доставка. Отдельные классы отвечают за зал, отзывы, закупки и учёт расходов.

Цены указаны в белорусских рублях: `29.99 BYN`. При оплате принимаются точка и запятая, например `pay 35.00` или `pay 35,00`. Внутри расчётов суммы хранятся целыми копейками. Класс `Money` преобразует ввод и формирует денежные значения для меню и чеков. Масса задаётся в граммах, время — в минутах.

## Структура

| Каталог | Назначение |
| --- | --- |
| include/stock, src/stock | Ингредиенты, поставщики, закупки и склад |
| include/menu, src/menu | Рецепты, размеры, тесто, соусы, начинки и меню |
| include/sales, src/sales | Покупатели, адреса, заказы, купоны, бонусы и платежи |
| include/kitchen, src/kitchen | Печь, задания выпечки, повар и упаковка |
| include/service, src/service | Курьеры, доставка, самовывоз, зал, отзывы и пиццерия |
| include/exceptions | 12 отдельных классов исключений |
| cli | Console и точка входа main |
| tests | Проверки предметных классов и сценария меню |
| tools/CheckModel.cmake | Проверка количественных требований по исходникам |

## Сборка и тестирование

Требуются CMake 3.24 и компилятор C++17. Команды выполняются из корня репозитория. При первой настройке скачивается doctest 2.4.11.

```sh
cmake -S lab2 -B build-lab2
cmake --build build-lab2 --config Release
ctest --test-dir build-lab2 -C Release --output-on-failure
cmake --install build-lab2 --config Release --prefix build-lab2/package
```

Для существующей локальной копии doctest допускается добавить параметр `-DFETCHCONTENT_SOURCE_DIR_DOCTEST=путь`. Интерфейс IDE для сборки и запуска тестов не требуется.

## Запуск

Из корня репозитория на Windows:

```sh
./build-lab2/package/pizzeria.exe
```

На Linux используется имя `pizzeria`. В скачанном архиве программа запускается из папки распаковки. Кодировка ввода и вывода Windows устанавливается в UTF-8.

Пример команд меню:

```text
menu
restock 1000
stock
add 1
total
pay 35.00
bake
pack
deliver
review 5 Хорошая пицца
new
exit
```

Пицца Classic стоит 29.99 BYN. При оплате 35.00 BYN сдача составляет 5.01 BYN. Приготовление одной пиццы расходует 210 г ингредиента с учётом потерь. Повторное пополнение того же ингредиента увеличивает существующий остаток. Выпечка требует оплаты, упаковка — выпечки, доставка — упаковки. Команда new начинает новый заказ. Классы рецептов, бонусов, закупок и бронирований дополнительно проверяются в юнит-тестах.

| Команда | Действие |
| --- | --- |
| menu | Просмотр меню |
| add COUNT | Добавление пицц в заказ |
| total | Расчёт суммы |
| pay CASH | Оплата и расчёт сдачи |
| receipt | Печать чека оплаченного заказа |
| bake | Списание ингредиента и выпечка |
| pack | Расход коробок и салфеток |
| deliver | Назначение курьера и завершение доставки |
| stock | Остатки ингредиентов |
| restock GRAMS | Приём ингредиента на склад |
| consume GRAMS | Списание ингредиента |
| review STARS TEXT | Публикация отзыва с оценкой от 1 до 5 |
| new | Новый заказ |
| exit | Завершение программы |

## Классы, поля, методы и связи

В колонке методов перечислены операции предметной области. Для каждого поля также доступен константный геттер Get с именем поля в PascalCase, например `grams_ → GetGrams()`, `on_shift_ → GetOnShift()`. Геттеры возвращают скаляр по значению или объект по константной ссылке. Конструктор по умолчанию создаёт указанные в заголовке начальные значения. Дополнительные конструкторы задают данные ингредиента, поставщика, адреса, размера, рецепта, пиццы, позиции меню, клиента, строки закупки, остатка, части рецепта и строки заказа.

| Класс и реализация | Назначение | Собственные поля | Предметные методы | Прямые связи |
| --- | --- | --- | --- | --- |
| [Ingredient](include/stock/Ingredient.h) · [cpp](src/stock/Ingredient.cpp) | Ингредиент и его пищевая ценность | `std::string name_`<br>`int calories_`<br>`int price_`<br>`bool allergen_` | `int Cost(int grams) const`<br>`int Energy(int grams) const`<br>`bool Allowed(bool avoid_allergens) const` | — |
| [Supplier](include/stock/Supplier.h) · [cpp](src/stock/Supplier.cpp) | Поставщик ингредиентов | `std::string name_`<br>`bool active_`<br>`int minimum_`<br>`int shipping_` | `int Quote(const Ingredient& ingredient, int grams) const`<br>`void Suspend()`<br>`void Resume()` | Ingredient |
| [PurchaseLine](include/stock/PurchaseLine.h) · [cpp](src/stock/PurchaseLine.cpp) | Строка закупки | `Ingredient ingredient_`<br>`Supplier supplier_`<br>`int grams_`<br>`int received_` | `int Total() const`<br>`void Receive(int grams)`<br>`int Outstanding() const` | Ingredient, Supplier |
| [PurchaseOrder](include/stock/PurchaseOrder.h) · [cpp](src/stock/PurchaseOrder.cpp) | Документ закупки | `Supplier supplier_`<br>`std::vector<PurchaseLine> lines_`<br>`bool closed_`<br>`int paid_` | `void Add(const PurchaseLine& line)`<br>`int Total() const`<br>`void Close(int payment)` | Supplier, PurchaseLine |
| [StockItem](include/stock/StockItem.h) · [cpp](src/stock/StockItem.cpp) | Остаток конкретного ингредиента | `Ingredient ingredient_`<br>`int grams_`<br>`int minimum_`<br>`int wasted_` | `void Receive(const PurchaseLine& line)`<br>`void Consume(int grams)`<br>`void Discard(int grams)`<br>`void Merge(const StockItem& other)` | Ingredient, PurchaseLine |
| [StockRoom](include/stock/StockRoom.h) · [cpp](src/stock/StockRoom.cpp) | Склад пиццерии | `std::vector<StockItem> items_`<br>`int capacity_`<br>`int deliveries_`<br>`int withdrawals_` | `void Store(const StockItem& item)`<br>`void Withdraw(const Ingredient& ingredient, int grams)`<br>`int CountLow() const` | Ingredient, StockItem |
| [RecipePart](include/menu/RecipePart.h) · [cpp](src/menu/RecipePart.cpp) | Количество ингредиента для одной пиццы | `Ingredient ingredient_`<br>`int grams_`<br>`int loss_percent_`<br>`std::string stage_` | `int Required(int count) const`<br>`int Cost(int count) const`<br>`void TakeFrom(StockRoom& stock, int count) const` | Ingredient, StockRoom |
| [Recipe](include/menu/Recipe.h) · [cpp](src/menu/Recipe.cpp) | Рецепт пиццы | `std::string name_`<br>`std::vector<RecipePart> parts_`<br>`int bake_minutes_`<br>`int portions_` | `void Add(const RecipePart& part)`<br>`int Cost() const`<br>`int RequiredGrams() const` | RecipePart |
| [PizzaSize](include/menu/PizzaSize.h) · [cpp](src/menu/PizzaSize.cpp) | Размер и количество кусков | `std::string name_`<br>`int diameter_`<br>`int slices_`<br>`int price_percent_` | `int ScalePrice(int base) const`<br>`bool Fits(int oven_diameter) const`<br>`int SliceWeight(int grams) const` | — |
| [Dough](include/menu/Dough.h) · [cpp](src/menu/Dough.cpp) | Заготовка теста | `Ingredient flour_`<br>`int grams_`<br>`int rested_minutes_`<br>`int required_minutes_` | `void Rest(int minutes)`<br>`bool Ready() const`<br>`int Use(int grams)` | Ingredient |
| [Sauce](include/menu/Sauce.h) · [cpp](src/menu/Sauce.cpp) | Порция соуса | `Ingredient ingredient_`<br>`int grams_`<br>`int serving_`<br>`bool spicy_` | `int Portions() const`<br>`void Pour(int portions)`<br>`bool Suitable(const Customer& customer) const` | Ingredient, Customer |
| [Topping](include/menu/Topping.h) · [cpp](src/menu/Topping.cpp) | Дополнительная начинка | `Ingredient ingredient_`<br>`int grams_`<br>`int surcharge_`<br>`bool available_` | `int Cost(int count) const`<br>`void StopSales()`<br>`bool CanServe(const Customer& customer) const` | Ingredient, Customer |
| [Pizza](include/menu/Pizza.h) · [cpp](src/menu/Pizza.cpp) | Пицца с рецептом и размером | `Recipe recipe_`<br>`PizzaSize size_`<br>`std::vector<Topping> toppings_`<br>`int base_price_` | `void AddTopping(const Topping& topping)`<br>`int Price() const`<br>`int Margin() const` | Recipe, PizzaSize, Topping |
| [MenuItem](include/menu/MenuItem.h) · [cpp](src/menu/MenuItem.cpp) | Позиция меню | `Pizza pizza_`<br>`std::string name_`<br>`bool available_`<br>`int sold_` | `int Quote(int count) const`<br>`void Sell(int count)`<br>`void StopSales()` | Pizza |
| [Menu](include/menu/Menu.h) · [cpp](src/menu/Menu.cpp) | Доступное меню | `std::vector<MenuItem> items_`<br>`int revision_`<br>`bool open_`<br>`std::string title_` | `void Add(const MenuItem& item)`<br>`const MenuItem& Find(const std::string& name) const`<br>`void Close()` | MenuItem |
| [Address](include/sales/Address.h) · [cpp](src/sales/Address.cpp) | Адрес доставки | `std::string street_`<br>`int house_`<br>`int distance_`<br>`std::string entrance_` | `void Validate() const`<br>`bool InRange(int maximum) const`<br>`std::string Label() const` | — |
| [Customer](include/sales/Customer.h) · [cpp](src/sales/Customer.cpp) | Покупатель | `std::string name_`<br>`Address address_`<br>`bool avoid_allergens_`<br>`int orders_` | `void ChooseAddress(const Address& address)`<br>`void RequireAllergenFree()`<br>`void RecordOrder(const Order& order)` | Address, Order |
| [LoyaltyAccount](include/sales/LoyaltyAccount.h) · [cpp](src/sales/LoyaltyAccount.cpp) | Бонусный счёт клиента | `Customer owner_`<br>`int points_`<br>`int earned_`<br>`int spent_` | `void Earn(const Payment& payment)`<br>`int Redeem(int points)`<br>`void TransferTo(LoyaltyAccount& target, int points)` | Customer, Payment |
| [Coupon](include/sales/Coupon.h) · [cpp](src/sales/Coupon.cpp) | Скидочный купон | `std::string code_`<br>`int percent_`<br>`int minimum_`<br>`bool used_` | `int Discount(const Order& order) const`<br>`void Redeem(Order& order)`<br>`bool Eligible(const Customer& customer) const` | Customer, Order |
| [OrderLine](include/sales/OrderLine.h) · [cpp](src/sales/OrderLine.cpp) | Строка заказа | `MenuItem item_`<br>`int quantity_`<br>`std::string comment_`<br>`bool packed_` | `void Increase(int count)`<br>`int Total() const`<br>`void Pack(const PizzaBox& box)` | MenuItem, PizzaBox |
| [Order](include/sales/Order.h) · [cpp](src/sales/Order.cpp) | Заказ покупателя | `std::vector<OrderLine> lines_`<br>`int discount_`<br>`bool confirmed_`<br>`bool cancelled_` | `void Add(const OrderLine& line)`<br>`int Subtotal() const`<br>`int Total() const`<br>`void ApplyDiscount(int amount)`<br>`void Confirm()`<br>`void Cancel()` | OrderLine |
| [Payment](include/sales/Payment.h) · [cpp](src/sales/Payment.cpp) | Платёж за заказ | `int amount_`<br>`int change_`<br>`bool captured_`<br>`bool refunded_`<br>`bool registered_` | `void Capture(const Order& order, int tendered)`<br>`int Refund()`<br>`int Net() const`<br>`void Register()` | Order |
| [CashRegister](include/sales/CashRegister.h) · [cpp](src/sales/CashRegister.cpp) | Касса | `int balance_`<br>`int revenue_`<br>`int refunds_`<br>`bool open_` | `void Accept(Payment& payment)`<br>`void Refund(Payment& payment)`<br>`int Close()` | Payment |
| [Oven](include/kitchen/Oven.h) · [cpp](src/kitchen/Oven.cpp) | Печь | `int temperature_`<br>`int required_temperature_`<br>`int diameter_`<br>`bool occupied_` | `void Heat(int degrees)`<br>`void Load(const Pizza& pizza)`<br>`void Unload()` | Pizza |
| [BakingTask](include/kitchen/BakingTask.h) · [cpp](src/kitchen/BakingTask.cpp) | Задание на выпечку | `Pizza pizza_`<br>`int elapsed_`<br>`int required_`<br>`bool started_` | `void Start(Oven& oven)`<br>`void Advance(int minutes)`<br>`bool Ready() const` | Pizza, Oven |
| [Cook](include/kitchen/Cook.h) · [cpp](src/kitchen/Cook.cpp) | Повар | `std::string name_`<br>`bool on_shift_`<br>`int prepared_`<br>`int minutes_worked_` | `void Prepare(const Recipe& recipe)`<br>`void Finish(BakingTask& task, Oven& oven)`<br>`void EndShift()` | Recipe, Oven, BakingTask |
| [Kitchen](include/kitchen/Kitchen.h) · [cpp](src/kitchen/Kitchen.cpp) | Кухня и очередь выпечки | `Cook cook_`<br>`Oven oven_`<br>`std::vector<BakingTask> queue_`<br>`int completed_` | `void Enqueue(const BakingTask& task)`<br>`void WarmUp()`<br>`void BakeNext()` | Oven, BakingTask, Cook |
| [PizzaBox](include/kitchen/PizzaBox.h) · [cpp](src/kitchen/PizzaBox.cpp) | Коробка для пиццы | `int diameter_`<br>`int available_`<br>`int cost_`<br>`bool recyclable_` | `bool Fits(const Pizza& pizza) const`<br>`int Take(int count)`<br>`void Restock(int count)` | Pizza |
| [Packaging](include/kitchen/Packaging.h) · [cpp](src/kitchen/Packaging.cpp) | Упаковка заказа | `PizzaBox boxes_`<br>`int napkins_`<br>`int packed_orders_`<br>`int used_boxes_` | `int RequiredBoxes(const Order& order) const`<br>`void Pack(const Order& order)`<br>`void RefillNapkins(int count)` | Order, PizzaBox |
| [Courier](include/service/Courier.h) · [cpp](src/service/Courier.cpp) | Курьер | `std::string name_`<br>`bool busy_`<br>`int distance_`<br>`int deliveries_` | `void Assign(const Address& address)`<br>`void Complete(const Address& address)`<br>`int Estimate(const Address& address) const` | Address |
| [DeliveryZone](include/service/DeliveryZone.h) · [cpp](src/service/DeliveryZone.cpp) | Зона и тариф доставки | `std::string name_`<br>`int maximum_`<br>`int per_km_`<br>`int free_from_` | `bool Covers(const Address& address) const`<br>`int Fee(const Address& address, const Order& order) const`<br>`int Remaining(const Address& address) const` | Address, Order |
| [Delivery](include/service/Delivery.h) · [cpp](src/service/Delivery.cpp) | Доставка оплаченного заказа | `Order order_`<br>`Address address_`<br>`bool dispatched_`<br>`bool delivered_` | `void Accept(const Order& order, const Address& address)`<br>`void Dispatch(Courier& courier, const DeliveryZone& zone)`<br>`void Complete(Courier& courier)` | Address, Order, Courier, DeliveryZone |
| [PickupSlot](include/service/PickupSlot.h) · [cpp](src/service/PickupSlot.cpp) | Интервал самовывоза | `int start_`<br>`int end_`<br>`int capacity_`<br>`int reserved_` | `bool Contains(int minute) const`<br>`void Reserve(const Order& order)`<br>`void Release()` | Order |
| [Table](include/service/Table.h) · [cpp](src/service/Table.cpp) | Стол в зале | `int number_`<br>`int seats_`<br>`int guests_`<br>`bool clean_` | `void Seat(int guests)`<br>`void Vacate()`<br>`void Clean()` | — |
| [Reservation](include/service/Reservation.h) · [cpp](src/service/Reservation.cpp) | Бронирование стола | `Customer customer_`<br>`int guests_`<br>`int minute_`<br>`bool active_` | `void CheckIn(Table& table)`<br>`void Postpone(int minutes)`<br>`void Cancel()` | Customer, Table |
| [Review](include/service/Review.h) · [cpp](src/service/Review.cpp) | Отзыв клиента | `Customer customer_`<br>`int stars_`<br>`std::string text_`<br>`bool published_` | `void Rate(int stars)`<br>`void Write(const std::string& text)`<br>`void Publish()` | Customer |
| [WorkShift](include/service/WorkShift.h) · [cpp](src/service/WorkShift.cpp) | Учёт смены повара | `Cook cook_`<br>`int start_`<br>`int end_`<br>`int rate_` | `void Finish(int minute)`<br>`int Duration() const`<br>`int Salary() const` | Cook |
| [Pizzeria](include/service/Pizzeria.h) · [cpp](src/service/Pizzeria.cpp) | Продажа и приготовление в пиццерии | `Menu menu_`<br>`CashRegister cash_`<br>`Kitchen kitchen_`<br>`int served_` | `void OpenMenu(const MenuItem& item)`<br>`Payment Sell(Order& order, int tendered)`<br>`void Bake(const BakingTask& task)` | MenuItem, Menu, Order, CashRegister, BakingTask, Kitchen |
| [Drink](include/menu/Drink.h) · [cpp](src/menu/Drink.cpp) | Напиток и запас порций | `std::string name_`<br>`int price_`<br>`int milliliters_`<br>`int available_` | `bool CanSell(int count) const`<br>`int Sell(int count)`<br>`void Restock(int count)` | — |
| [MealDeal](include/menu/MealDeal.h) · [cpp](src/menu/MealDeal.cpp) | Набор из пиццы и напитка | `Pizza pizza_`<br>`Drink drink_`<br>`int discount_` | `int Price() const`<br>`bool CanServe(int count) const`<br>`int Sell(int count)` | Pizza, Drink |
| [LunchOffer](include/menu/LunchOffer.h) · [cpp](src/menu/LunchOffer.cpp) | Скидка в заданное время | `MenuItem item_`<br>`int start_`<br>`int end_`<br>`int percent_` | `bool IsActive(int minute) const`<br>`int Discount(int count) const`<br>`int Quote(int minute, int count) const` | MenuItem |
| [WasteRecord](include/stock/WasteRecord.h) · [cpp](src/stock/WasteRecord.cpp) | Акт списания ингредиента | `Ingredient ingredient_`<br>`int grams_`<br>`std::string reason_`<br>`bool booked_` | `int Cost() const`<br>`void Apply(StockRoom& stock)`<br>`std::string Describe() const` | Ingredient, StockRoom |
| [StockAudit](include/stock/StockAudit.h) · [cpp](src/stock/StockAudit.cpp) | Инвентаризация остатков | `StockRoom snapshot_`<br>`bool captured_` | `void Capture(const StockRoom& stock)`<br>`int TotalGrams() const`<br>`int Difference(const StockRoom& current) const` | StockRoom |
| [SupplierInvoice](include/stock/SupplierInvoice.h) · [cpp](src/stock/SupplierInvoice.cpp) | Счёт по закрытой закупке | `PurchaseOrder purchase_`<br>`int paid_`<br>`bool settled_` | `void Issue(const PurchaseOrder& purchase)`<br>`int Outstanding() const`<br>`void Settle(int amount)` | PurchaseOrder |
| [Receipt](include/sales/Receipt.h) · [cpp](src/sales/Receipt.cpp) | Чек для оплаченного заказа | `Order order_`<br>`Payment payment_`<br>`std::string shop_` | `void Validate() const`<br>`int Total() const`<br>`std::string Text() const` | Order, Payment |
| [RefundRequest](include/sales/RefundRequest.h) · [cpp](src/sales/RefundRequest.cpp) | Запрос на возврат платежа | `Payment& payment_`<br>`std::string reason_`<br>`bool resolved_` | `void Validate() const`<br>`void Resolve(CashRegister& cash)`<br>`int RequestedAmount() const` | Payment, CashRegister |
| [ExpenseBook](include/sales/ExpenseBook.h) · [cpp](src/sales/ExpenseBook.cpp) | Учёт закупок, зарплаты и списаний | `int purchases_`<br>`int wages_`<br>`int waste_` | `void RecordPurchase(const PurchaseOrder& purchase)`<br>`void RecordShift(const WorkShift& shift)`<br>`void RecordWaste(const WasteRecord& record)`<br>`int Total() const` | PurchaseOrder, WorkShift, WasteRecord |
| [ThermalBag](include/service/ThermalBag.h) · [cpp](src/service/ThermalBag.cpp) | Термосумка для готовых пицц | `std::vector<Pizza> pizzas_`<br>`int capacity_`<br>`bool clean_` | `void Load(const Pizza& pizza)`<br>`Pizza Unload()`<br>`void Clean()` | Pizza |
| [DeliveryRoute](include/service/DeliveryRoute.h) · [cpp](src/service/DeliveryRoute.cpp) | План выездов по адресам | `std::vector<Address> stops_`<br>`int capacity_`<br>`bool finished_` | `void AddStop(const Address& address)`<br>`int TotalDistance() const`<br>`void Finish()` | Address |
| [SalesReport](include/sales/SalesReport.h) · [cpp](src/sales/SalesReport.cpp) | Сводка оплаченных продаж | `std::vector<Order> orders_`<br>`std::vector<Payment> payments_` | `void Record(const Order& order, const Payment& payment)`<br>`int Revenue() const`<br>`int AverageCheck() const` | Order, Payment |
| [Money](include/sales/Money.h) · [cpp](src/sales/Money.cpp) | Сумма в BYN, разбор ввода и отображение рублей и копеек | `int kopecks_` | `Parse(const std::string&)`<br>`FromKopecks(int)`<br>`ToString() const`<br>`ToKopecks() const` | — |
| [Console](cli/Console.h) · [cpp](cli/Console.cpp) | Консольный интерфейс | shop_, order_, payment_, stock_, packaging_, courier_, baked_, packed_ | Run, Execute, Stock, Pay, Bake, Pack, Deliver, Reset | Pizzeria, Order, Payment, StockRoom, Packaging, Courier |

## Исключения

Каждый класс наследуется от std::runtime_error. Собственных полей у исключений нет; сообщение хранится в базовом классе и доступно через what(). Конструктор задаёт тип ошибки в сообщении. В интерфейсе исключения перехватываются через std::exception.

| Класс | Причина |
| --- | --- |
| [InvalidAmount](include/exceptions/InvalidAmount.h) | Недопустимая денежная сумма |
| [InvalidQuantity](include/exceptions/InvalidQuantity.h) | Недопустимое количество |
| [StockShortage](include/exceptions/StockShortage.h) | Недостаточно запасов |
| [InactiveSupplier](include/exceptions/InactiveSupplier.h) | Поставщик приостановлен |
| [EmptyRecipe](include/exceptions/EmptyRecipe.h) | Пустой рецепт |
| [UnavailableItem](include/exceptions/UnavailableItem.h) | Позиция отсутствует или недоступна |
| [InvalidAddress](include/exceptions/InvalidAddress.h) | Некорректный адрес или зона доставки |
| [InvalidOrder](include/exceptions/InvalidOrder.h) | Недопустимое состояние заказа или операции |
| [InsufficientPayment](include/exceptions/InsufficientPayment.h) | Недостаточно денег для операции |
| [UnavailableOven](include/exceptions/UnavailableOven.h) | Печь не готова или занята |
| [UnavailableCourier](include/exceptions/UnavailableCourier.h) | Курьер занят или не назначен |
| [InvalidReservation](include/exceptions/InvalidReservation.h) | Недопустимое бронирование |

## Проверки, документация и выпуск версии

В тестах проверяются успешные операции, запреты по состоянию, недопустимые суммы и количества, недостаток запасов, недоступная печь и курьер, повторный платёж, возврат, скидки, бонусы и бронирование. Отдельный сценарий запускает приложение и проходит заказ от оплаты до доставки.

Для локального покрытия с GCC и gcovr:

```sh
cmake -S lab2 -B build-lab2-coverage -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-lab2-coverage
ctest --test-dir build-lab2-coverage --output-on-failure
gcovr --root . --filter 'lab2/(src|include|cli)/' --txt --fail-under-line 90.01 build-lab2-coverage
```

При доступном Doxygen:

```sh
cmake -S lab2 -B build-lab2
cmake --build build-lab2 --target docs
explorer.exe build-lab2/html/index.html
```

Пайплайн находится в [.github/workflows/lab2.yml](../.github/workflows/lab2.yml). Задание verify запускает тесты и проверку модели, требует покрытие выше 90%, выполняет cppcheck и создаёт Doxygen. Задание package собирает и проверяет готовые программы для Windows и Linux. Тег lab2-v* запускает публикацию архивов в Releases. Артефакт lab2-reports содержит XML покрытия и HTML-документацию.

Пример выпуска версии из ветки лабораторной после коммита и отправки изменений:

```sh
git switch lab2/pizzeria
git push origin lab2/pizzeria
git tag -a lab2-v1.0.3 -m "Pizzeria version 1.0.3"
git push origin lab2-v1.0.3
```
