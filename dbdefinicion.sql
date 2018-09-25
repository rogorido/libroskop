BEGIN TRANSACTION;
DROP TABLE IF EXISTS `libros_categorias`;
CREATE TABLE IF NOT EXISTS `libros_categorias` (
	`libro_categoria_id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`libro_id`	INTEGER,
	`categoria_id`	INTEGER,
	FOREIGN KEY(`libro_id`) REFERENCES `libro`(`libro_id`),
	FOREIGN KEY(`categoria_id`) REFERENCES `categorias`(`categoria_id`)
);
DROP TABLE IF EXISTS `libros_autores`;
CREATE TABLE IF NOT EXISTS `libros_autores` (
	`libro_autor_id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`libro_id`	INTEGER,
	`autor_id`	INTEGER,
	FOREIGN KEY(`autor_id`) REFERENCES `autores`(`autor_id`),
	FOREIGN KEY(`libro_id`) REFERENCES `libro`(`libro_id`)
);
DROP TABLE IF EXISTS `libros_editores`;
CREATE TABLE IF NOT EXISTS `libros_editores` (
	`libro_editor_id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`libro_id`	INTEGER,
	`editor_id`	INTEGER,
	FOREIGN KEY(`editor_id`) REFERENCES `autores`(`autor_id`),
	FOREIGN KEY(`libro_id`) REFERENCES `libro`(`libro_id`)
);
DROP TABLE IF EXISTS `libro`;
CREATE TABLE IF NOT EXISTS `libro` (
	`libro_id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`titulo`	TEXT,
	`subtitulo`	TEXT,
	`editorial`	TEXT,
	`lugar`	TEXT,
	`fecha`	TEXT,
	`lengua` TEXT,
	`localizacion`	TEXT
);
DROP TABLE IF EXISTS `categorias`;
CREATE TABLE IF NOT EXISTS `categorias` (
	`categoria_id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`categoria`	TEXT NOT NULL
);
INSERT INTO `categorias` VALUES (1,'Literatura');
INSERT INTO `categorias` VALUES (2,'Literatura española');
INSERT INTO `categorias` VALUES (3,'Literatura hispanoamericana');
INSERT INTO `categorias` VALUES (4,'Política');
INSERT INTO `categorias` VALUES (5,'Economía');
DROP TABLE IF EXISTS `autores`;
CREATE TABLE IF NOT EXISTS `autores` (
	`autor_id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`nombre`	TEXT,
	`apellido`	TEXT
);
COMMIT;
