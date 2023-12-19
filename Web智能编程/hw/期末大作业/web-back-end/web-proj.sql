/*
 Navicat Premium Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 80031 (8.0.31)
 Source Host           : localhost:3306
 Source Schema         : web-proj

 Target Server Type    : MySQL
 Target Server Version : 80031 (8.0.31)
 File Encoding         : 65001

 Date: 20/12/2023 01:21:20
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for students
-- ----------------------------
DROP TABLE IF EXISTS `students`;
CREATE TABLE `students`  (
  `student_id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `major` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `phone_number` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `gender` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `GPA` decimal(3, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`student_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 46 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of students
-- ----------------------------
INSERT INTO `students` VALUES (2, '李四', '电子信息', 'lisi@example.com', '13987654321', '女', 3.25);
INSERT INTO `students` VALUES (3, '王五', '化学', 'wangwu@example.com', '13611112222', '男', 3.80);
INSERT INTO `students` VALUES (4, '赵六', '心理学', 'zhaoliu@example.com', '13533334444', '女', 3.65);
INSERT INTO `students` VALUES (5, '刘七', '物理学', 'liuqi@example.com', '13755556666', '男', 3.45);
INSERT INTO `students` VALUES (6, '陈八', '数学', 'chenba@example.com', '13877778888', '女', 3.70);
INSERT INTO `students` VALUES (7, '杨九', '生物学', 'yangjiu@example.com', '13999991111', '男', 3.55);
INSERT INTO `students` VALUES (8, '黄十', '经济学', 'huangshi@example.com', '13566667777', '女', 3.90);
INSERT INTO `students` VALUES (9, '吴十一', '历史学', 'wueleven@example.com', '13688889999', '男', 3.30);
INSERT INTO `students` VALUES (10, '朱十二', '地理学', 'zhutwelve@example.com', '13700001111', '女', 3.75);
INSERT INTO `students` VALUES (11, '冯十三', '政治学', 'fengthirteen@example.com', '13822223333', '男', 3.20);
INSERT INTO `students` VALUES (12, '韩十四', '文学', 'hanfourteen@example.com', '13944445555', '女', 3.85);
INSERT INTO `students` VALUES (13, '许十五', '语言学', 'xufifteen@example.com', '13577778888', '男', 3.40);
INSERT INTO `students` VALUES (14, '杜十六', '艺术学', 'dusixteen@example.com', '13699990000', '女', 3.95);
INSERT INTO `students` VALUES (15, '胡十七', '音乐学', 'huseventeen@example.com', '13711112222', '男', 3.15);
INSERT INTO `students` VALUES (16, '马十八', '体育学', 'maeighteen@example.com', '13833334444', '女', 3.80);
INSERT INTO `students` VALUES (17, '朱十九', '工程学', 'zhunineteen@example.com', '13955556666', '男', 3.25);
INSERT INTO `students` VALUES (18, '田二十', '医学', 'tiantwenty@example.com', '13566667777', '女', 3.70);
INSERT INTO `students` VALUES (19, '张三', '计算机科学', 'zhangsan@example.com', '13812345678', '男', 3.50);
INSERT INTO `students` VALUES (20, '李四', '电子工程', 'lisi@example.com', '13987654321', '女', 3.25);
INSERT INTO `students` VALUES (21, '王五', '化学', 'wangwu@example.com', '13611112222', '男', 3.80);
INSERT INTO `students` VALUES (22, '赵六', '心理学', 'zhaoliu@example.com', '13533334444', '女', 3.65);
INSERT INTO `students` VALUES (23, '刘七', '物理学', 'liuqi@example.com', '13755556666', '男', 3.45);
INSERT INTO `students` VALUES (24, '陈八', '数学', 'chenba@example.com', '13877778888', '女', 3.70);
INSERT INTO `students` VALUES (25, '杨九', '生物学', 'yangjiu@example.com', '13999991111', '男', 3.55);
INSERT INTO `students` VALUES (26, '黄十', '经济学', 'huangshi@example.com', '13566667777', '女', 3.90);
INSERT INTO `students` VALUES (27, '吴十一', '计算机科学', 'wueleven@example.com', '13688889999', '男', 3.30);
INSERT INTO `students` VALUES (28, '朱十二', '地理学', 'zhutwelve@example.com', '13700001111', '女', 3.75);
INSERT INTO `students` VALUES (29, '冯十三', '经济学', 'fengthirteen@example.com', '13822223333', '男', 3.20);
INSERT INTO `students` VALUES (30, '韩十四', '计算机科学', 'hanfourteen@example.com', '13944445555', '女', 3.85);
INSERT INTO `students` VALUES (31, '许十五', '生物学', 'xufifteen@example.com', '13577778888', '男', 3.40);
INSERT INTO `students` VALUES (32, '杜十六', '物理学', 'dusixteen@example.com', '13699990000', '女', 3.95);
INSERT INTO `students` VALUES (33, '胡十七', '地理学', 'huseventeen@example.com', '13711112222', '男', 3.15);
INSERT INTO `students` VALUES (34, '马十八', '物理学', 'teenger@example.com', '13833334444', '女', 3.80);
INSERT INTO `students` VALUES (35, '朱十九', '计算机科学', 'zhunineteen@example.com', '13955556666', '男', 3.25);
INSERT INTO `students` VALUES (36, '田二十', '生物学', 'tiantwenty@example.com', '13566667777', '女', 3.70);

SET FOREIGN_KEY_CHECKS = 1;
