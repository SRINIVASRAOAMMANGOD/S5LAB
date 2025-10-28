Create a Function named GetDepartmentManagerName(p_dept_id) that accepts a department ID and returns the full name of the employee who is the manager of that department.

Create a Procedure named PromoteToManager(p_emp_id). This procedure will:

Find the dept_id of the employee specified by p_emp_id.

Update the Departments table to set the manager_id for that department to p_emp_id.

Update the Employees table to set the is_manager flag to TRUE for that employee.

(Optional Challenge): Find the old manager of the department (if one existed) and set their is_manager flag to FALSE.

Create a Trigger named prevent_manager_transfer that fires BEFORE UPDATE on the Employees table. This trigger must enforce the following business rule:

Check if the employee being updated is currently a manager (OLD.is_manager is TRUE).

Check if the update is attempting to change their department (OLD.dept_id <> NEW.dept_id).

If both conditions are true, the trigger must stop the operation and SIGNAL a custom error with the message, "A manager cannot be transferred to another department. Demote them first."




create table employees(empid INT PRIMARY KEY,empname VARCHAR(10),ismanager BOOLEAN,deptid INT ,FOREIGN KEY(deptid) references department(deptid));

create table departmentdeptid INT PRIMARY KEY,deptnameVARCHAR(10),managerid INT,FOREIGN KEY(managerid) references employees(empid));


first, you create the tables, and second, you insert the data in a specific order.
Create the employees table without the foreign key constraint.
Create the department table with its foreign key. This works because the employees table now exists.
CREATE TABLE employees (
    empid INT PRIMARY KEY,
    empname VARCHAR(10),
    ismanager BOOLEAN,
    deptid INT
);
CREATE TABLE department (
    deptid INT PRIMARY KEY,
    deptname VARCHAR(10),
    managerid INT,
    FOREIGN KEY (managerid) REFERENCES employees(empid)
);
Add the missing foreign key to the employees table using ALTER TABLE
ALTER TABLE employees
ADD CONSTRAINT fk_dept
FOREIGN KEY (deptid) REFERENCES department(deptid);
ALTER TABLE employees DROP FOREIGN KEY fk_dept;

Inserting the Data
To insert data, you must temporarily break the dependency by using NULL for a foreign key. This requires that the foreign key columns (managerid and deptid) are allowed to be NULL.

Insert an employee but leave their deptid as NULL. This employee will be the first manager.

SQL

-- Let's say the CEO (empid 101) is created first and isn't in a department yet
INSERT INTO employees(empid, empname, ismanager, deptid) VALUES (101, 'Alice', TRUE, NULL);
Insert a department and assign that employee as the manager. This works because the employee (ID 101) now exists.

SQL

INSERT INTO department(deptid, deptname, managerid) VALUES (1, 'HR', 101);
Finally, update the first employee to place them in the department you just created.

SQL

UPDATE employees SET deptid = 1 WHERE empid = 101;
By following this order, you satisfy the foreign key constraints at each step.


Other Method
-- Step 1: Disable the foreign key checks
SET FOREIGN_KEY_CHECKS = 0;

-- Step 2: Insert the data. The order doesn't matter now.
-- You can insert the department first...
INSERT INTO department(deptid, deptname, managerid) VALUES (1, 'HR', 101);

-- ...and then insert the employee, even though the department didn't exist when the check was on.
INSERT INTO employees(empid, empname, ismanager, deptid) VALUES (101, 'Alice', TRUE, 1);

-- Step 3: Re-enable the foreign key checks for all future operations
SET FOREIGN_KEY_CHECKS = 1;

DELIMITER //
create function GetDepartmentManagerName(dept_id INT) returns VARCHAR(10)
DETERMINSTIC 
DECLARE name VARCHAR(10);

SELECT empname into name from employees where deptid=dept_id and ismanager=1;
return name
//
DELIMITER ;
BEGIN ... END block: Required to wrap the function body.

LIMIT 1: Ensures only one result is returned (important if multiple managers exist).

DETERMINISTIC: Correct spelling (you had DETERMINSTIC).

Semicolon after RETURN: Needed to terminate the statement.

DELIMITER //
create function GetDepartmentManagerName(dept_id INT) returns VARCHAR(10)
DETERMINISTIC
BEGIN
DECLARE name VARCHAR(10);

SELECT empname into name from employees where deptid=dept_id and ismanager=1 LIMIT 1;
return name;
END //
DELIMITER ;



DELIMITER //
CREATE PROCEDURE PromotedToManager(IN emp_id INT)
BEGIN
DECLARE DEP INT;
DECLARE firstmanager int;

select deptid into DEP from employees where empid=emp_id;
select managerid into firstmanager from department where deptid=DEP;
IF emp_id = firstmanager THEN
SIGNAL SQLSTATE '45000'
SET MESSAGE_TEXT='already manager';
ELSE

update employees set ismanager=1 where empid=emp_id;
update employees set ismanager=0 where empid=firstmanager;
update department set managerid=emp_id where deptid=DEP;
END IF;
END //
DELIMITER;

more correct 

DELIMITER //
CREATE PROCEDURE PromtedToManager(IN emp_id INT)
BEGIN
    DECLARE DEP INT;
    DECLARE firstmanager INT;

    SELECT deptid INTO DEP FROM employees WHERE empid = emp_id;
    SELECT managerid INTO firstmanager FROM department WHERE deptid = DEP;

    IF emp_id = firstmanager THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'already manager';
    ELSE
        -- First, demote the old manager, but only if one exists
        IF firstmanager IS NOT NULL THEN
            UPDATE employees SET ismanager = 0 WHERE empid = firstmanager;
        END IF;
        
        -- Next, update the department to assign the new manager
        UPDATE department SET managerid = emp_id WHERE deptid = DEP;
        
        -- Finally, promote the new employee
        UPDATE employees SET ismanager = 1 WHERE empid = emp_id;
    END IF;
END //
DELIMITER ;



DELIMITER //
create trigger prevent_manager_transfer before update on employees

for each row
begin
if (OLD.ismanager is TRUE and OLD.deptid <> NEW.deptid) THEN
SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT="A manager cannot be transferred to another department. Demote them first.";
end if;
end//
DELIMITER ;







1. Using SET (Modifying the NEW Row)You use SET almost exclusively in a BEFORE trigger to change the data that is about to be inserted or updated.It's used for validation and standardization. You use it with the NEW keyword to directly change the value of a column.BEFORE INSERT Trigger ExampleHere, SET is used to change the NEW.email value before it gets saved to the database.SQLDELIMITER //
CREATE TRIGGER before_patient_insert
BEFORE INSERT ON Patients
FOR EACH ROW
BEGIN
    -- This SET modifies the data in the row being inserted.
    SET NEW.email = LOWER(NEW.email);
END; //
DELIMITER ;
2. Using UPDATE ... SET (Modifying Other Tables)You use UPDATE ... SET almost exclusively in an AFTER trigger to make a change to a different table as a consequence of the first event.It's used for logging, auditing, or keeping tables in sync.AFTER INSERT Trigger ExampleHere, UPDATE ... SET is used to change a different table (Doctors) after an appointment is successfully inserted.SQLDELIMITER //
CREATE TRIGGER after_appointment_insert
AFTER INSERT ON Appointments
FOR EACH ROW
BEGIN
    -- This UPDATE modifies a row in a different table.
    UPDATE Doctors
    SET total_appts = total_appts + 1
    WHERE doctor_id = NEW.doctor_id;
END; //
DELIMITER ;
Key Differences Command	What It Does	When to Use	Example
SET	Assigns a value. Used on NEW to change a column's value before it's saved.	BEFORE Trigger		SET NEW.email = LOWER(NEW.email);




UPDATE ... SET	Runs a full UPDATE command. Used to change data in another table.	AFTER Trigger	UPDATE Doctors SET total_appts = total_appts + 1 WHERE ...;







