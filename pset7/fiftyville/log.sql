-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get description of the event
SELECT description FROM crime_scene_reports
WHERE month=7 AND day=28 AND street='Chamberlin Street';
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- Read interview transcripts
SELECT name, transcript FROM interviews
WHERE month=7 AND day=28 AND transcript LIKE '%courthouse%';
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning,
-- before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Get license plates of cars leaving the courthouse after 10:15
SELECT hour, minute, license_plate FROM courthouse_security_logs
WHERE month=7 AND day=28 AND hour=10 AND minute >= 15 AND minute <= 25 AND activity='exit';

-- Get passports of people by license plates
SELECT name, phone_number, passport_number FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs
WHERE month=7 AND day=28 AND hour=10 AND minute >= 15 AND activity='exit');

-- Get all bank accounts of people withdrowing money at the day on Fifer street
SELECT account_number FROM atm_transactions
WHERE month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw';

-- Get all phone-call recievers
SELECT caller, receiver, duration FROM phone_calls
WHERE month=7 AND day=28 AND duration < 60;

-- List of suspects
SELECT name FROM people
WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE month=7 AND day=28 AND hour=10 AND minute >= 15 AND activity='exit')
AND phone_number IN
(SELECT caller FROM phone_calls
WHERE month=7 AND day=28 AND duration < 60);

-- Get id of the earliest flight on next morning
SELECT * FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE month=7 AND day=29 AND city='Fiftyville'
ORDER BY hour ASC
LIMIT 1;

-- Get list of passengers of the flight
SELECT passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = (SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE month=7 AND day=29 AND city='Fiftyville'
ORDER BY hour ASC
LIMIT 1);

-- Short list of suspects
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE passport_number IN
(SELECT passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = (SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE month=7 AND day=29 AND city='Fiftyville'
ORDER BY hour ASC
LIMIT 1))
AND license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE month=7 AND day=28 AND hour=10 AND minute >= 15 AND minute <= 25 AND activity='exit')
AND phone_number IN
(SELECT caller FROM phone_calls
WHERE month=7 AND day=28 AND duration < 60)
AND account_number IN
(SELECT account_number FROM atm_transactions
WHERE month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw');

-- Suspect: Ernest

-- Get the name of helper
SELECT name FROM people
WHERE phone_number=
(SELECT receiver FROM phone_calls
WHERE month=7 AND day=28 AND duration < 60 AND caller=
(SELECT phone_number FROM people
WHERE name='Ernest'));

-- Get the place where the thief escaped

SELECT city FROM airports
WHERE id=
(SELECT destination_airport_id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE month=7 AND day=29 AND city='Fiftyville'
ORDER BY hour ASC
LIMIT 1);

