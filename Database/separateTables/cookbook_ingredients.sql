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
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-10-03 23:44:27
