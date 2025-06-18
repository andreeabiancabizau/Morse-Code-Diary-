# Morse Code Diary 📝🔤

A command-line diary application written in C++ that allows you to record, view, and search daily journal entries encoded in **Morse Code**.

Includes two apps:
- `app_1`: For writing, modifying, and deleting entries
- `app_2`: For reading, searching, and exporting entries

---

## ✨ Features

- Encode diary entries into Morse code
- View raw or decoded entries
- Search entries by keywords
- Modify or delete existing entries
- Export search results to file
- Full error handling (e.g. invalid dates, missing files)
- Color-coded terminal output

---

## 📁 Run Example 

./app_1 add_entry 2025 06 18 "today is nice"  

./app_1 view_entries 

./app_1 view_entries --decoded

./app_1 modify_entry 2025 06 17 “this “is an update”

./app_1 delete_entry 2025 06 18

./app_1 view_log 



./app_2 view_entry 2025 06 17

./app_2 view_entry 2025 06 17 --decoded

./app_2 search_word diary

./app_2 export_search_results

./app_2 view_export


