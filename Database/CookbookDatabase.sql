CREATE DATABASE  IF NOT EXISTS `cookbook` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `cookbook`;
-- MySQL dump 10.13  Distrib 8.0.38, for macos14 (arm64)
--
-- Host: localhost    Database: cookbook
-- ------------------------------------------------------
-- Server version	9.0.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `categories`
--

DROP TABLE IF EXISTS `categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `categories` (
  `recipe_id` int NOT NULL AUTO_INCREMENT,
  `category_name` varchar(45) NOT NULL,
  `iconName` varchar(45) NOT NULL,
  PRIMARY KEY (`recipe_id`),
  UNIQUE KEY `category_name_UNIQUE` (`category_name`),
  UNIQUE KEY `iconName_UNIQUE` (`iconName`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `categories`
--

LOCK TABLES `categories` WRITE;
/*!40000 ALTER TABLE `categories` DISABLE KEYS */;
INSERT INTO `categories` VALUES (1,'Перші страви','main.png'),(2,'Другі страви','starters.png'),(3,'Салати','salad.png'),(4,'Закуски','snack.png'),(5,'Десерти','dessert.png');
/*!40000 ALTER TABLE `categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dishes`
--

DROP TABLE IF EXISTS `dishes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `dishes` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dishes`
--

LOCK TABLES `dishes` WRITE;
/*!40000 ALTER TABLE `dishes` DISABLE KEYS */;
INSERT INTO `dishes` VALUES (5,'Бургер'),(8,'Желе'),(2,'Картопля'),(4,'Кебаб'),(7,'Овочевий салат'),(3,'Рагу'),(10,'Салат зелений'),(1,'Суп'),(6,'Тушковане м\'ясо'),(9,'Шарлотка');
/*!40000 ALTER TABLE `dishes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ingredients`
--

DROP TABLE IF EXISTS `ingredients`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ingredients` (
  `id` int NOT NULL AUTO_INCREMENT,
  `ingredient_name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  UNIQUE KEY `ingredient_name_UNIQUE` (`ingredient_name`),
  KEY `idx_ingredient_name` (`ingredient_name`)
) ENGINE=InnoDB AUTO_INCREMENT=72 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ingredients`
--

LOCK TABLES `ingredients` WRITE;
/*!40000 ALTER TABLE `ingredients` DISABLE KEYS */;
INSERT INTO `ingredients` VALUES (5,'Борошно пшеничне 1г.'),(39,'Булка для бургера'),(43,'Буряк'),(19,'Ванільний цукор'),(9,'Вода'),(64,'Вода питна'),(65,'Гвоздика'),(62,'Жовтки'),(61,'Заправка'),(11,'Капуста білокачанна'),(41,'Капуста пекінська'),(44,'Картопля'),(24,'Кориця мелена'),(34,'Кріп сушений'),(17,'Крохмаль картопляний'),(1,'Куряче філе'),(68,'Лавровий лист'),(63,'Лимонна кислота'),(58,'Лист лавровий'),(66,'Маса вареного м\'яса'),(35,'Маса напівфабрикату'),(57,'Масло вершкове'),(16,'Молоко'),(53,'Морква'),(70,'Морква (для бульйону)'),(71,'Морква (для страви)'),(13,'Огірки свіжі'),(42,'Огірок солоний'),(2,'Олія соняшникова рафінована'),(59,'Перець духмяний'),(69,'Перець духмяний горошком'),(37,'Перець чорний мелений'),(54,'Петрушка корінь'),(6,'Петрушка сушена'),(12,'Помідори свіжі'),(26,'Салат зелений'),(60,'Селера корінь'),(33,'Сир-кисломолочний'),(8,'Сіль харчова'),(40,'Соус \"Кетчуп\"'),(67,'Соус сметанний'),(15,'Сушений чебрець'),(55,'Томатне пюре'),(4,'Томатне пюре 20%'),(23,'Хліб (батон)'),(7,'Хмелі-сунелі'),(3,'Цибуля ріпчаста'),(18,'Цукор'),(10,'Часник сушений'),(56,'Чорнослив'),(14,'Яйця'),(38,'Яловича відбивна готова'),(36,'Яловичина'),(32,'Яловичина (котлетне м\'ясо)');
/*!40000 ALTER TABLE `ingredients` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nationalities`
--

DROP TABLE IF EXISTS `nationalities`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `nationalities` (
  `id` int NOT NULL AUTO_INCREMENT,
  `nationality_name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `nationality_name_UNIQUE` (`nationality_name`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nationalities`
--

LOCK TABLES `nationalities` WRITE;
/*!40000 ALTER TABLE `nationalities` DISABLE KEYS */;
INSERT INTO `nationalities` VALUES (4,'Американська кухня'),(5,'Грецька кухня'),(3,'Грузинська кухня'),(7,'Італійська кухня'),(2,'Турецька кухня'),(1,'Українська кухня'),(6,'Французька кухня');
/*!40000 ALTER TABLE `nationalities` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `recipe_details`
--

DROP TABLE IF EXISTS `recipe_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `recipe_details` (
  `recipe_id` int NOT NULL AUTO_INCREMENT,
  `cooking_technology` text NOT NULL,
  `recipe_notes` text NOT NULL,
  PRIMARY KEY (`recipe_id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `recipe_details`
--

LOCK TABLES `recipe_details` WRITE;
/*!40000 ALTER TABLE `recipe_details` DISABLE KEYS */;
INSERT INTO `recipe_details` VALUES (1,'1. Порційні шматки курки обсмажити. \n2. Додати нарізану кільцями і пасеровану цибулю, томатне пюре, пасероване борошно. \n3. Додати бульйон або воду, сушені петрушку, хмелі-сунелі та часник, тушкувати до готовності.','• Замість курячого філе\nможна використовувати\nрозібрану курячу гомілку.\n• Подавайте чахохбілі\nз гречаною кашею,\nкартоплею або рисом.\n• Регулюйте консистенцію\nстрави за допомогою води\nчи бульйону. Рідка частина\nстрави повинна бути\nсоусоподібною.\n• Страва обов\'язково\nповинна бути ароматною.\nІнакше – це просто підлива.\n• Замість хмелі-сунелі\nможна використовувати\nкоріандр або паприку.\n• Смажте курку на пательні\nневеликими порціями.\nЯкщо смажити одразу багато\nм\'яса, виділятиметься багато\nрідини, і м\'ясо варитиметься.\nЦе критично для смаку. '),(2,'1. Нарізане на шматки котлетне м\'ясо подрібнити на м\'ясорубці. Додати яйце та хмелі-сунелі. Змішати фарш.  2. Котлетну масу розділити на порції, округлити та приплюснути, всередину вкласти кисломолочний сир та сформувати напівфабрикати овальної форми.  3. Запекти в духовій шафі при температурі 180 0 С протягом 3 хвилин. Посипати сушеним кропом.','• Головне, не перетримати кебаби у духовці, бо вони вийдуть сухими та несмачними.  • Я раджу подавати кебаби з соусом каркаде, цибулевим, томатним з імбиром або соусом «кетчуп».'),(3,'1. Відбити яловичу відбивну, додати сіль, перець. \n2. Обсмажити на пательні при температурі 130 0 С протягом 7-10 хв. \n3. Огірки нарізати кружельцями, капусту – нашаткувати. 4. Булку розрізати навпіл, змастити соусом, викласти відбивну, огірок солений, капусту.','• Смажте м‘ясо з мінімальною кількістю олії. Так воно буде більш соковитим та корисним. \n• М‘ясо не повинно подаватися холодним – холодну їжу діти не їстимуть. \n• М‘ясо не повинно бути пересушеним. Якщо у вас товстий шматок м‘яса, смажте його 7-10 хвилин, якщо тонкий – менше. \n• Смажте м‘ясо на пательні невеликими порціями. Якщо смажити одразу багато м‘яса, виділятиметься багато рідини, і фактично м‘ясо варитиметься. Це критично для смаку. \n• Якщо у вас немає змоги смажити м‘ясо на пательні, запікайте його у духовці. \n• Якщо у вас немає пекінської капусти, можна замінити її на звичайну білокачанну.'),(4,'1. Приготувати овочевий бульйон. Великими шматками нарізати попередньо підготовлені овочі: корінь петрушки, половину моркви та цибулі. Додати в киплячу воду. Варити 20 хвилин, додати лавровий лист, перець духмяний, хмелісунелі. Шматки овочів вийняти через 30 хвилин кипіння бульйону. Додати сіль. \n2. Підготовлену картоплю нарізати брусочками, покласти в бульйон та варити 10-15 хвилин. \n3. Потім покласти підготовлений варений буряк, пасеровані на вершовому маслі з олією овочі (половина моркви та цибули, нарізані кубиком) та томатне пюре з цукром. Додати чорнослив. Варити ще 5 хвилин.','• Замість чорносливу можна додати копчену грушу. \n• Засмажку робіть на вершковому маслі, аби борщ мав насичений смак. Ненасичений борщ діти не їстимуть.'),(5,'1. Підготовлені моркву та селеру подрібнити на крупній терці. Цибулю розрізати навпіл. Додати в киплячу воду. Через 15 хвилин варіння вийняти цибулю, додати сіль. \n2. Почищену картоплю нарізати кубиками середнього розміру, додати в суп. Варити ще 10 хвилин та додати вершкове масло. \n3. Окремо приготувати заправку. Для цього в окремій посудині жовтки змішати з водою, в якій попередньо розчинена лимонна кислота. \n4. За 5 хвилин до кінця варки додати заправку, інтенсивно перемішуючи суп.','• Варити бульйон потрібно до появи овочевого смаку. Проте чим більший об‘єм, тим довше потрібно готувати бульйон. \n• Додавати заправку до супу потрібно за 5 хвилин до видачі страви, а не до кінця варіння.'),(6,'1. Яловичину зварити з духмяним перцем, гвоздикою та лавровим листом. \n2. Варене м\'ясо нарізати брусочками довжиною 30-40 мм, масою 5-7 г та з’єднати з перетертою вареною морквою. \n3. Потім м\'ясо залити сметанним соусом, додати чорний мелений перець та варити на слабкому вогні 5-10 хв. В посудині з закритою кришкою.','• Яловичина може бути жорсткою, тому я раджу попередньо її відварити, щоб вона стала м\'якішою. Так, я розумію, що вона може втратити у смаку, проте стане ніжнішою. Також у цьому допоможе тривале тушкування м\'яса у сметанному соусі. \n• Замість яловичини, можна використовувати свинину. \n• Традиційно бефстроганов подається з картопляним пюре.'),(7,'1. Білокачанну капусту нашаткувати. \n2. Підготовлені помідори та огірки нарізати скибками. \n3. Яйця зварити, почистити, нарізати кубиком. \n4. Всі компоненти змішати, полити олією, посипати чебрецем та сіллю.','• Використовуйте свіжі помідори та огірки перші 2 місяці осені, так собівартість салату буде менше, аніж взимку, та й користі більше. \n• Нарізайте помідори перед видачею салату, аби вони не потекли. \n• Не переваріть яйця, щоб вони не посиніли. Діти не довіряють синім яйцям. Оптимальний час для варки яєць – 10 хвилин.'),(8,'1. Половину молока вилити у каструлю та поставити на вогонь.  2. Другу половину молока перелити у ємність, додати крохмаль, цукор та добре збовтати.  3. Додати молочно-крохмальну суміш до підігрітого молока та, постійно помішуючи, довести до кипіння. Потрібно постійно помішувати, щоб молоко не пригоріло.  4. Після того, як молочна суміш прокипить протягом 5-10 хв., необхідно розлити її порційно, дати остигнути та поставити в холодильник на 4-6 годин, щоб бланманже застиг.','• При додаванні крохмалю суміш потрібно ретельно перемішувати, аби у масі не утворювалися грудочки, і вона не пригоріла.  • Одразу розливайте масу по чашках, аби вона не почала застигати у каструлі.  • За смаком ви можете варіювати кількість ванільного цукру.  • Якщо за собівартістю страва виходить дорогою, то відміряйте менше бланманже на порцію. Не забувайте, ми сповідуємо принцип: «Краще – менше, але краще!»'),(9,'1. Зрізати з хліба скоринку. Хлібний м’якуш нарізати на тонкі скибки. \n2. Молоко підігріти, зняти з вогню, ретельно помішуючи, додати яйця, цукор та корицю. \n3. Скибки хліба викласти одним шаром в форму для запікання та залити молочно-яєчною сумішшю. \n4. Запікати в духовій шафі при температурі 180 0 С до готовності, коли хліб повністю поглине молоко та на поверхні утвориться золотава скоринка.','• Це дуже смачна страва з невеликою собівартістю. \n• Важливо рівно викладати шматочки хлібу один на один, аби після приготування та нарізання на порції, шматочки страви гарно виглядали на тарілці та не розпадалися. \n• Можна використовувати вчорашній хліб.'),(10,'1. Підготовлений салат нарізати великими шматками, помідори та огірки – скибочками. \n2. Всі інгредієнти з’єднати, заправити олією та сіллю.','• Використовуйте свіжі огірки та помідори перші 2 місяці осені, так собівартість салату буде менше, аніж взимку, та й користі більше. \n• Нарізайте помідори перед видачею салату, аби вони не потекли.');
/*!40000 ALTER TABLE `recipe_details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `recipe_ingredients`
--

DROP TABLE IF EXISTS `recipe_ingredients`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `recipe_ingredients` (
  `recipe_id` int NOT NULL,
  `ingredient_id` int NOT NULL,
  `weight_grams` decimal(6,2) DEFAULT NULL,
  `quantity` varchar(45) DEFAULT NULL,
  `ready_made_weight` decimal(6,2) DEFAULT NULL,
  PRIMARY KEY (`recipe_id`,`ingredient_id`),
  KEY `idx_ingredient_id` (`ingredient_id`),
  CONSTRAINT `recipe_ingredients_ibfk_1` FOREIGN KEY (`recipe_id`) REFERENCES `recipes` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `recipe_ingredients_ibfk_2` FOREIGN KEY (`ingredient_id`) REFERENCES `ingredients` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `recipe_ingredients`
--

LOCK TABLES `recipe_ingredients` WRITE;
/*!40000 ALTER TABLE `recipe_ingredients` DISABLE KEYS */;
INSERT INTO `recipe_ingredients` VALUES (1,1,84.00,NULL,NULL),(1,2,6.00,NULL,NULL),(1,3,60.00,NULL,NULL),(1,4,11.20,NULL,NULL),(1,5,0.80,NULL,NULL),(1,6,0.50,NULL,NULL),(1,7,0.30,NULL,NULL),(1,8,0.40,NULL,NULL),(1,9,10.00,NULL,NULL),(1,10,0.30,NULL,NULL),(2,7,0.40,NULL,NULL),(2,8,2.00,NULL,NULL),(2,14,NULL,'1/5 шт.',NULL),(2,32,146.20,NULL,NULL),(2,33,8.00,NULL,NULL),(2,34,NULL,NULL,0.50),(2,35,NULL,NULL,120.00),(3,8,1.00,NULL,NULL),(3,36,58.30,NULL,NULL),(3,37,0.04,NULL,NULL),(3,38,NULL,NULL,35.00),(3,39,NULL,'1 шт.',NULL),(3,40,4.00,NULL,NULL),(3,41,8.00,NULL,NULL),(3,42,3.00,NULL,NULL),(4,2,2.00,NULL,NULL),(4,3,9.60,NULL,NULL),(4,7,0.40,NULL,NULL),(4,8,1.20,NULL,NULL),(4,18,1.20,NULL,NULL),(4,43,40.80,NULL,NULL),(4,44,53.20,NULL,NULL),(4,53,10.20,NULL,NULL),(4,54,2.60,NULL,NULL),(4,55,9.20,NULL,NULL),(4,56,4.00,NULL,NULL),(4,57,2.00,NULL,NULL),(4,58,0.01,NULL,NULL),(4,59,0.01,NULL,NULL),(4,64,140.00,NULL,NULL),(5,3,3.60,NULL,NULL),(5,8,1.20,NULL,NULL),(5,9,106.00,NULL,NULL),(5,44,21.30,NULL,NULL),(5,53,23.00,NULL,NULL),(5,57,0.01,NULL,NULL),(5,60,29.40,NULL,NULL),(5,61,NULL,NULL,160.00),(5,62,4.00,NULL,NULL),(5,63,0.20,NULL,NULL),(5,64,28.00,NULL,NULL),(6,8,0.50,NULL,NULL),(6,36,110.00,NULL,NULL),(6,37,0.10,NULL,NULL),(6,53,12.50,NULL,NULL),(6,65,0.04,NULL,NULL),(6,66,NULL,NULL,50.00),(6,67,NULL,NULL,50.00),(6,68,0.04,NULL,NULL),(6,69,0.08,NULL,NULL),(6,70,2.50,NULL,NULL),(6,71,12.50,NULL,NULL),(7,2,5.00,NULL,NULL),(7,8,0.50,NULL,NULL),(7,11,51.40,NULL,NULL),(7,12,27.10,NULL,NULL),(7,13,28.80,NULL,NULL),(7,14,NULL,'1/3 шт.',NULL),(7,15,0.10,NULL,NULL),(8,16,127.50,NULL,NULL),(8,17,15.00,NULL,NULL),(8,18,12.75,NULL,NULL),(8,19,0.60,NULL,NULL),(9,8,0.50,NULL,NULL),(9,14,NULL,'1/5 шт.',NULL),(9,16,100.10,NULL,NULL),(9,18,10.20,NULL,NULL),(9,19,0.60,NULL,NULL),(9,23,30.00,NULL,NULL),(9,24,1.30,NULL,NULL),(10,2,5.00,NULL,NULL),(10,8,0.50,NULL,NULL),(10,12,34.10,NULL,NULL),(10,13,45.00,NULL,NULL),(10,26,41.70,NULL,NULL);
/*!40000 ALTER TABLE `recipe_ingredients` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `recipe_portions`
--

DROP TABLE IF EXISTS `recipe_portions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `recipe_portions` (
  `id` int NOT NULL AUTO_INCREMENT,
  `recipe_id` int NOT NULL,
  `portion_size_grams` decimal(5,2) NOT NULL,
  `calories` decimal(6,2) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  KEY `recipe_portions_ibfk_1` (`recipe_id`),
  CONSTRAINT `recipe_portions_ibfk_1` FOREIGN KEY (`recipe_id`) REFERENCES `recipes` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `recipe_portions`
--

LOCK TABLES `recipe_portions` WRITE;
/*!40000 ALTER TABLE `recipe_portions` DISABLE KEYS */;
INSERT INTO `recipe_portions` VALUES (1,1,100.00,218.80),(2,6,100.00,125.00),(3,7,100.00,93.00),(4,8,150.00,125.10),(5,9,150.00,176.92),(6,10,100.00,69.00),(12,2,100.00,260.46),(13,3,100.00,244.77),(14,4,200.00,103.00),(15,5,200.00,56.07);
/*!40000 ALTER TABLE `recipe_portions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `recipes`
--

DROP TABLE IF EXISTS `recipes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `recipes` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `category_id` int NOT NULL,
  `nationality_id` int NOT NULL,
  `isFavourite` tinyint(1) NOT NULL DEFAULT '0',
  `dish_id` int NOT NULL,
  `cooking_technology_id` int NOT NULL,
  `recipe_notes_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_categories` (`category_id`),
  KEY `fk_nationalities` (`nationality_id`),
  KEY `fk_dish` (`dish_id`),
  KEY `fk_cooking_technology_idx` (`cooking_technology_id`),
  KEY `fk_recipe_notes_idx` (`recipe_notes_id`),
  CONSTRAINT `fk_categories` FOREIGN KEY (`category_id`) REFERENCES `categories` (`recipe_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_cooking_technology` FOREIGN KEY (`cooking_technology_id`) REFERENCES `recipe_details` (`recipe_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_dish` FOREIGN KEY (`dish_id`) REFERENCES `dishes` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_nationalities` FOREIGN KEY (`nationality_id`) REFERENCES `nationalities` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_recipe_notes` FOREIGN KEY (`recipe_notes_id`) REFERENCES `recipe_details` (`recipe_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `recipes`
--

LOCK TABLES `recipes` WRITE;
/*!40000 ALTER TABLE `recipes` DISABLE KEYS */;
INSERT INTO `recipes` VALUES (1,'Чахохбілі з куркою',1,3,0,3,1,1),(2,'Кебаб з сиром',2,2,0,4,2,2),(3,'Бургер з яловичиною',4,4,0,5,3,3),(4,'Борщ з картоплею',1,1,0,1,4,4),(5,'Авголемоно',1,5,0,1,5,5),(6,'Бефстроганов з вареної яловичини',2,1,0,6,6,6),(7,'Салат з овочів',3,1,0,7,7,7),(8,'Бланманже (молочне желе)',5,6,0,8,8,8),(9,'Пан де калатрава (Шарлотка з хліба та молока)',5,7,0,9,9,9),(10,'Салат зелений з огірками та помідорами',3,1,0,10,10,10);
/*!40000 ALTER TABLE `recipes` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-10-03 23:43:41
