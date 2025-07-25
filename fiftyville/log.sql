-- Keep a log of any SQL queries you execute as you solve the mystery.
-- .schema exported to temp.txt
-- What Happened? Thief stole the duck and then, shortly afterwards, took a flight out of town with the help of an accomplice.
-- When? July 28, 2024 and that it took place on Humphrey Street.
    --OG Clues: stole duck -> flight out of fiftyville -> had an accomplice -> on 28/07/2024 at Humphrey Street

-- FIRST QUERY: SELECT * FROM crime_scene_reports; (just to get a feel of what is happening)
-- REFINED: SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street"; (all data is from 2024)

-- NEW CLUES 1:
    -- time = 10:15 AM
    -- location = bakery
    -- witnesses = 3 (each of their interview transcripts mention the word 'bakery')
    -- new tables accessable: interviews, bakery_security_logs, people(tentatively)

-- SECOND QUERY: SELECT * FROM interviews WHERE transcript LIKE "%bakery%"; (unexpectedly fiftyville cops are efficient)

-- NEW CLUES 2:
    --Ruth: (thief got into a car between 10:15 - 10:25; look at the cars that left from bakery parking lot)
    --Eugene: (withdrew money from ATM on Leggett Street prior to 10:15 AM)
    --Raymond: (called someone for < 60 seconds while leaving bakery; asked to book tickets for July 29, 2024)[here the accomplice enters]

-- THIRD QUERY:
    --1. SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25; [8 possible licence_plate]
    --2. SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = "Leggett Street";
            -- SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
            -- [8 possible account_number]
    --3. SELECT * FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration <= 60; [10 possible caller & receiver{ACCOMPLICE}]

-- NEW CLUES 3:
    -- Now we know have a shortlist of 8-10 people and we know their licence_plate, account_number & (caller & receiver{ACCOMPLICE}) deets
    -- new tables accessable: people, flights, airports, bank_accounts
    -- now we can narrow down from the people table. we have possible phone_number & license_plate
    -- but first, let's deal with the account_number bs to narrow results down

-- FOURTH QUERY:
    --1. SELECT * FROM bank_accounts WHERE account_number IN
    --  (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
    -- [8 possible people we have now]
    --2. SELECT * FROM people WHERE license_plate IN
    --   (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
    --   AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration <= 60);
    -- [BILLA SHOT: we now have 4 possible thiefs]

--NEW CLUES 4:
    -- Since this is an important matter and the result data is handful, we will shortlist perps manually.
    -- we now have 2 possible thiefs
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+

    -- ALSO, ONE OF THE RECIEVER NUMBERS WILL BE THE ACCOMPLICE, FOLLOWING ARE THE SHORTLISTED RESULTS
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2024 | 7     | 28  | 45       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2024 | 7     | 28  | 49       |
+-----+----------------+----------------+------+-------+-----+----------+

-- FIFTH QUERY:
    -- Now we reverse engineer, we'll find flight details from passport_number
    -- SELECT * FROM passengers WHERE passport_number IN (3592750733, 5773159633);
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 18        | 3592750733      | 4C   |
| 24        | 3592750733      | 2C   |
| 36        | 5773159633      | 4A   |
| 54        | 3592750733      | 6C   |
+-----------+-----------------+------+
    -- Now we will check the flight details from the flight_id
    -- SELECT * FROM flights WHERE id IN (SELECT flight_id FROM passengers WHERE passport_number IN (3592750733, 5773159633));
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2024 | 7     | 29  | 16   | 0      |
| 24 | 7                 | 8                      | 2024 | 7     | 30  | 16   | 27     |
| 36 | 8                 | 4                      | 2024 | 7     | 29  | 8    | 20     |
| 54 | 8                 | 5                      | 2024 | 7     | 30  | 10   | 19     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
    -- BRUCE IS THE ONLY ONE LOGICALLY MAKING SENSE (DIANA RETURNED BACK)
    -- THEREFORE (375) 555-8161 IS THE reciever number. ACCOMPLICE IS
    -- SELECT * FROM people WHERE phone_number = "(375) 555-8161";
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+
    -- LET'S CHECK THE SOURCE AND DESTINATION AIRPORTS ONCE
    -- SELECT * FROM airports WHERE id IN (8, 4);
+----+--------------+-----------------------------+---------------+
| id | abbreviation |          full_name          |     city      |
+----+--------------+-----------------------------+---------------+
| 4  | LGA          | LaGuardia Airport           | New York City |
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville    |
+----+--------------+-----------------------------+---------------+
EZPZ.
