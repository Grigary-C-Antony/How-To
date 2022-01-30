const express = require("express");
const bodyParser = require("body-parser");
const mysql = require("mysql");

const app = express();
const port = process.env.PORT || 3001;

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//TODO SQL Codes here
const pool = mysql.createPool({
  connectionLimit: 10,
  host: "localhost",
  user: "root",
  password: "password",
  database: "nodejs",
});
// create operation Crud
app.post("/add/", (req, res) => {
  sqlquery = "INSERT INTO crudtable SET ?";
  params = req.body;
  pool.getConnection((error, connection) => {
    if (error) throw error;
    console.log(`connected as id ${connection.threadId}`);
    connection.query(sqlquery, params, (err, rows) => {
      connection.release();
      if (!err) {
        res.send(`Added ${params.id}`);
      } else {
        console.log("error", error);
      }
    });
  });
});
//read operaton cRud
app.get("/", (req, res) => {
  sqlquery = "SELECT * from crudtable";
  pool.getConnection((error, connection) => {
    if (error) throw error;
    console.log(`connected as id ${connection.threadId}`);
    connection.query(sqlquery, (err, rows) => {
      connection.release();
      if (!err) {
        res.send(rows);
      } else {
        console.log("error", error);
      }
    });
  });
});
//read operation specific to id
app.get("/:id", (req, res) => {
  sqlquery = "SELECT * from crudtable WHERE id=?";
  pool.getConnection((error, connection) => {
    if (error) throw error;
    console.log(`connected as id ${connection.threadId}`);
    connection.query(sqlquery, [req.params.id], (err, rows) => {
      connection.release();
      if (!err) {
        res.send(rows);
      } else {
        console.log("error", error);
      }
    });
  });
});

//delete operation specific to id
app.delete("/:id", (req, res) => {
  sqlquery = "DELETE from crudtable WHERE id=?";
  pool.getConnection((error, connection) => {
    if (error) throw error;
    console.log(`connected as id ${connection.threadId}`);
    connection.query(sqlquery, [req.params.id], (err, rows) => {
      connection.release();
      if (!err) {
        res.send(`deleted ${rows}`);
      } else {
        console.log("error", error);
      }
    });
  });
});
//update operation specific to id
app.put("/update", (req, res) => {
  sqlquery = "UPDATE crudtable SET Name=?,Email=?,Phone=? WHERE ID = ?";
  const { ID, Name, Email, Phone } = req.body;
  pool.getConnection((error, connection) => {
    if (error) throw error;
    console.log(`connected as id ${connection.threadId}`);
    connection.query(sqlquery, [Name, Email, Phone, ID], (err, rows) => {
      connection.release();
      if (!err) {
        res.send(`updated ${Name}`);
      } else {
        console.log("error", error);
      }
    });
  });
});

//TODO SQL Codes here

app.listen(port, function (err) {
  if (err) console.log("Error in server setup");
  console.log(`Server listening on Port ${port}`);
});
