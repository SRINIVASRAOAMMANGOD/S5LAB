Problem: A Simple Clinic Management System
You need to design the database logic for a small clinic. The system will manage doctors, patients, and their appointments.

Schema
Doctors (doctor_id, doctor_name, specialty, hire_date)

doctor_id is the primary key.

Patients (patient_id, patient_name, email, registration_date)

patient_id is the primary key. email must be unique.

Appointments (appt_id, patient_id, doctor_id, appt_date, status)

appt_id is the primary key.

patient_id is a foreign key to the Patients table.

doctor_id is a foreign key to the Doctors table.

The status can only be 'Scheduled', 'Completed', or 'Cancelled'.

Tasks
Part 1: Setup and Basic Management (Exp 1, 2, 6)
Create Tables: Write the CREATE TABLE statements for all three tables with the correct primary keys, foreign keys, and constraints (e.g., UNIQUE, ENUM for status).

Insert Data: Write INSERT statements to add at least 2 doctors, 3 patients, and 4 appointments.

Create Users:

Create a user named receptionist who has SELECT, INSERT, and UPDATE permissions on the Appointments table only.

Create a user named auditor who only has SELECT permission on all tables.

Part 2: Reporting and Queries (Exp 3, 4, 7)
List Recent Patients: Write a query to list the names and registration dates of all patients who registered in the last year.

Find Appointment Details: Write a query that lists the patient's name, the doctor's name, and the appointment date for all 'Scheduled' appointments. This requires a three-table join.

Count Doctor's Appointments: Write a query to display each doctor's name and the total number of appointments they have.

Find Above-Average Patients: Find the names of all patients who have had more appointments than the average number of appointments per patient. This requires a subquery.

Part 3: Views (Exp 5)
Create a View: Create a view named UpcomingAppointments that shows the appt_id, patient_name, doctor_name, specialty, and appt_date for all appointments with a status of 'Scheduled' and an appt_date in the future.

Part 4: Automation and Business Logic (Exp 8)
Create a Function: Create a function named GetPatientAppointmentCount(p_patient_id) that accepts a patient_id and returns the total number of appointments that patient has had.

Create a Trigger: Create a trigger named prevent_duplicate_booking that fires BEFORE INSERT on the Appointments table. The trigger must check if the same patient is already booked with the same doctor on the same day. If a duplicate is found, it must stop the insertion using SIGNAL with a custom error message.

Create a Procedure: Create a procedure named CancelAppointment(p_appt_id). This procedure will:

Check if the appointment exists.

Update the appointment's status to 'Cancelled'.

Return a confirmation message (e.g., SELECT 'Appointment cancelled successfully.').

create table doctor(doctorid INT PRIMARY KEY,doctorname VARCHAR(10),specialty VARCHAR(10),hiredate DATE);
create table patient(patientid INT PRIMARY KEY,patientname VARCHAR(10),email VARCHAR(10) UNIQUE,registrationdate DATE);
create table appointments(apptid INT PRIMARY KEY,patientid INT,doctorid INT,status ENUM('Scheduled', 'Completed', 'Cancelled'),FOREIGN KEY(patientid) REFERENCES patient(patientid),FOREIGN KEY(doctorid) REFERENCES doctor(doctorid));

INSERT INTO doctor (doctorid, doctorname, specialty, hiredate) VALUES
(101, 'Dr. Smith', 'Cardio', '2020-05-10'),
(102, 'Dr. Jones', 'Pedia', '2021-08-22');
INSERT INTO patient (patientid, patientname, email, registrationdate) VALUES
(1, 'John Doe', 'j@doe.com', '2023-01-15'),
(2, 'Jane Roe', 'j@roe.com', '2023-03-11'),
(3, 'Sam Ray', 's@ray.com', '2024-06-01');
INSERT INTO appointments (apptid, patientid, doctorid, status) VALUES
(1001, 1, 101, 'Scheduled'),
(1002, 2, 102, 'Scheduled'),
(1003, 1, 101, 'Completed'),
(1004, 3, 102, 'Cancelled');
	List Recent Patients: Write a query to list the names and registration dates of all patients who registered in the last year.
select patientname,registrationdate from patient where registrationdate < '2024-12-30' and registrationdate > '2023-12-31';
SELECT patientname, registrationdate 
FROM patient 
WHERE YEAR(registrationdate) = 2024;

SELECT patientname, registrationdate
FROM patient
WHERE registrationdate >= CURRENT_DATE - INTERVAL 1 YEAR;

select p.patientname,d.doctorname,d.hiredate from patient p,doctor d,appointments a where status='Scheduled' ;
SELECT
    p.patient_name,
    d.doctor_name,
    a.appt_date
FROM
    Appointments a
JOIN
    Patients p ON a.patient_id = p.patient_id
JOIN
    Doctors d ON a.doctor_id = d.doctor_id
WHERE
    a.status = 'Scheduled';
select patientname,doctorname,hiredate from appointments natural join  patient natural join  doctor where status='Scheduled' ;

ALTER TABLE appointments ADD COLUMN appt_date DATE AFTER doctorid;

select d.doctorname,count(a.apptdate) from doctor d, appointments a where d.doctorid=a.doctorid and status='Scheduled' group by doctorname;

INSERT INTO Appointments (apptid, patientid, doctorid, apptdate, status) VALUES
(1001, 1, 101, '2025-10-25', 'Scheduled'),
(1002, 2, 102, '2025-11-05', 'Scheduled'),
(1003, 1, 101, '2025-09-15', 'Completed'),
(1004, 3, 102, '2025-08-20', 'Cancelled');

select p.patientname from patient p JOIN appointments a ON p.patientid=a.patientid GROUP BY patientname having count(a.apptid)>(
select AVG(appcount) from (select count(apptid) as appcount from appointments group by patientid)  as patientavgcount
);

create view UpcomingAppointments as select a.apptid,p.patientname,d.doctorname,d.specialty, a.apptdate from appointments a JOIN patient p ON a.patientid=p.patientid JOIN doctor d ON a.doctorid=d.doctorid where a.status="Scheduled" and a.apptdate> CURRENT_DATE;
SELECT * FROM UpcomingAppointments;


DELIMITER // 
create function GetPatientAppointmentCount(patient_id INT) returns INT
DETERMINISTIC
begin
DECLARE totalappointmant INT;
select count(s.status) into totalappointmant from appointments s where patientid=patient_id;
return totalappointmant;
end // 
DELIMITER ;


DELIMITER //

CREATE PROCEDURE CancelAppointment(IN p_appt_id INT)
BEGIN
    DECLARE app_count INT;

    -- Check if the appointment exists AND is 'Scheduled'
    SELECT COUNT(*)
    INTO app_count
    FROM appointments
    WHERE apptid = p_appt_id AND `status` = 'Scheduled';

    -- The count will be 1 if found, 0 otherwise
    IF app_count = 1 THEN
        -- It exists, so update it
        UPDATE appointments
        SET `status` = 'Cancelled'
        WHERE apptid = p_appt_id;
        
        -- Return a success message
        SELECT 'Appointment cancelled successfully.' AS message;
        
    ELSE
        -- It doesn't exist or isn't 'Scheduled'
        SELECT 'Error: Appointment not found or is not in Scheduled state.' AS message;
    END IF;

END //

DELIMITER ;

SIGNAL is used only for throwing an error and stopping the procedure. It's not used to send a success message

DELIMITER //

CREATE PROCEDURE CancelAppointment(IN p_appt_id INT)
BEGIN
    DECLARE current_status VARCHAR(20);

    -- 1. Get the current status of the appointment
    SELECT `status`
    INTO current_status
    FROM appointments
    WHERE apptid = p_appt_id;

    -- 2. Check the status and act
    IF current_status IS NULL THEN
        -- ERROR CASE 1: Appointment doesn't exist
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Error: Appointment not found.';
        
    ELSEIF current_status = 'Completed' OR current_status = 'Cancelled' THEN
        -- ERROR CASE 2: Already done or cancelled
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Error: Appointment is already completed or cancelled.';
        
    ELSEIF current_status = 'Scheduled' THEN
        -- SUCCESS CASE: It is scheduled, so cancel it
        UPDATE appointments
        SET `status` = 'Cancelled'
        WHERE apptid = p_appt_id;
        
        -- Return the success message (as required by the original problem)
        SELECT 'Appointment cancelled successfully.' AS message;
        
    END IF;

END //

DELIMITER ;

The OLD variable only exists for UPDATE and DELETE operations

DELIMITER //

CREATE TRIGGER prevent_duplicate_booking
BEFORE INSERT ON appointments
FOR EACH ROW
BEGIN
    DECLARE booking_count INT;

    -- Check if a 'Scheduled' or 'Completed' appointment already exists
    -- for this patient, with this doctor, on this day.
    SELECT COUNT(*)
    INTO booking_count
    FROM appointments
    WHERE
        patientid = NEW.patientid
        AND doctorid = NEW.doctorid
        AND apptdate = NEW.apptdate
        AND `status` IN ('Scheduled', 'Completed');

    -- If we found a booking (count > 0), throw an error
    IF booking_count > 0 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Duplicate Booking: This patient is already booked with this doctor on this day.';
    END IF;

END //

DELIMITER ;
