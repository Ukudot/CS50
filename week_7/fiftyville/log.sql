-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Read the description of the crime scene
SELECT description
  FROM crime_scene_reports
 WHERE street = 'Humphrey Street'
   AND year = 2021
   AND month = 7
   AND day = 28;
-- Description:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. 
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.
-- Read transcription of the witnesses's interviews
SELECT name, transcription
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28;
-- Here are only the meaningfull interviews:
-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--
-- Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--
-- Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- Accordingly with the first interview we checked the plates of card leaving the bakery park between 10:15 and 10:25
SELECT licencse_plate
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute >= 15
   AND minute <= 25;
-- license plates:
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55
-- Using these informations and the second interview we can interpolate the owner of the car with the people that withdraw money that day:
SELECT p.name, a_t.amount 
  FROM bank_accounts AS b_a
	INNER JOIN people AS p
	ON b_a.person_id = p.id 
	   AND p.license_plate IN 
		(SELECT license_plate 
		   FROM bakery_security_logs 
		  WHERE year = 2021 
		    AND month = 7 
		    AND day = 28 
		    AND hour = 10 
		    AND minute >= 15 
		    AND minute <= 25 
		    AND activity = 'exit')
	
	INNER JOIN atm_transactions AS a_t
	ON b_a.account_number = a_t.account_number 
	   AND a_t.year = 2021 
	   AND a_t.month = 7 
	   AND a_t.day = 28
           AND a_t.atm_location = 'Leggett Street'	
	   AND a_t.transaction_type = 'withdraw';
-- Result (name|amount withdrawn):
-- Bruce|50
-- Diana|35
-- Iman|20
-- Luca|48
-- Furthermore we can interpolate this informations with the ones given in the third interview:
SELECT p.name, a_t.amount 
  FROM bank_accounts AS b_a
	INNER JOIN people AS p
	ON b_a.person_id = p.id 
	   AND p.license_plate IN 
		(SELECT license_plate 
		   FROM bakery_security_logs 
		  WHERE year = 2021 
		    AND month = 7 
		    AND day = 28 
		    AND hour = 10 
		    AND minute >= 15 
		    AND minute <= 25 
		    AND activity = 'exit')
	   AND p.phone_number IN
		(SELECT caller
		   FROM phone_calls
		  WHERE year = 2021
		    AND month = 7
		    AND day = 28
		    AND duration < 60)
	
	INNER JOIN atm_transactions AS a_t
	ON b_a.account_number = a_t.account_number 
	   AND a_t.year = 2021 
	   AND a_t.month = 7 
	   AND a_t.day = 28 
	   AND a_t.transaction_type = 'withdraw';
-- Result(name|amunt withdrawn):
-- Bruce|50
-- Diana|35
-- Now we can check who was the receiver 
SELECT id, name 
  FROM people 
 WHERE phone_number = 
	(SELECT receiver 
	   FROM phone_calls 
	  WHERE year = 2021 
	    AND month = 7 
	    AND day = 28 
	    AND caller = 
		(SELECT phone_number 
		   FROM people 
		  WHERE name = 'Bruce'));
-- 864400|Robin
-- Bruce called to Robin that day
SELECT id, name 
  FROM people 
 WHERE phone_number = 
	(SELECT receiver 
	   FROM phone_calls 
	  WHERE year = 2021 
	    AND month = 7 
	    AND day = 28 
	    AND caller = 
		(SELECT phone_number 
		   FROM people 
		  WHERE name = 'Diana'));
-- 847116|Philip
-- While Diana called Philip that day
-- So both called someone during that day, thus we can check who take a flight from fiftiville the next day:
SELECT id, day, hour, minute, desttination_airport_id
  FROM flights 
 WHERE origin_airport_id =
	(SELECT id 
	   FROM airports 
	   WHERE city = 'Fiftyville') 
   AND id IN 
	(SELECT flight_id 
	   FROM passengers 
	  WHERE passport_number = 
		(SELECT passport_number 
		   FROM people 
		   WHERE name = 'Bruce')) 
   AND day = 29 
 ORDER BY hour ASC, minute ASC;
-- Result:
-- 36|29|8|20|4
SELECT id, day, hour, minute, desttination_airport_id
  FROM flights 
 WHERE origin_airport_id =
	(SELECT id 
	   FROM airports 
	   WHERE city = 'Fiftyville') 
   AND id IN 
	(SELECT flight_id 
	   FROM passengers 
	  WHERE passport_number = 
		(SELECT passport_number 
		   FROM people 
		   WHERE name = 'Diana')) 
   AND day = 29 
 ORDER BY hour ASC, minute ASC;
-- Result:
-- 18|29|16|0|6
-- Meanwhile the flight in table for the 07/29/2021 were:
SELECT id, day, hour, minute 
  FROM flights 
 WHERE origin_airport_id = 
	(SELECT id 
	   FROM airports 
	  WHERE city = 'Fiftyville') 
   AND day = 29
   AND month = 7
   AND year = 2021
 ORDER BY hour ASC, minute ASC;
-- Result:
-- 36|29|8|20
-- 43|29|9|30
-- 23|29|12|15
-- 53|29|15|20
-- 18|29|16|0
-- We can finally say that Bruce is the thief cause he took the earliest flight accordigly with the third interview.
-- We can also check the destination of the flight:
SELECT city
  FROM airports
 WHERE id = 4;
-- Destination:
-- New York City;
-- In coclusion Bruce stole the duck and the next day he took a flight to New York City; the ticket was bought by Robin, his accomplice.
