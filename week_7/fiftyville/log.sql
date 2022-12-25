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
-- Accordingly with the first interviews I checked the plates of card leaving the bakery park between 10:15 and 10:25
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
