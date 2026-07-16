def no_space(s):
    for ch in s:
        if ch == " ":
            return False
    return True
#공백이 존재하는지 확인하는 함수

def add_book(books, parts):
    #명령어 형식
    if len(parts) != 3:
        print("ERROR: add 명령어 형식이 올바르지 않습니다. (예: add 책이름 수량)")
        return
    #parts 속 내용을 한 번에 옮기는 코드
    _, name, qty_str = parts
    if not no_space(name):
        print("ERROR: 책이름에는 공백을 포함할 수 없습니다.")
        return
    if not qty_str.isdigit():
        print("ERROR: 수량은 0 이상의 정수여야 합니다.")
        return
    qty = int(qty_str)
    books[name] = books.get(name, 0) + qty
    print(f"{name} {qty}권 등록 완료 (현재 재고: {books[name]}권)")


def borrow_book(books, loans, parts):
    if len(parts) != 3:
        print("ERROR: borrow 명령어 형식이 올바르지 않습니다. (예: borrow 사용자 책이름)")
        return
    _, user, book = parts
    if not no_space(user) or not no_space(book):
        print("ERROR: 사용자 이름과 책 이름에는 공백을 포함할 수 없습니다.")
        return
    if book not in books:
        print(f"ERROR: '{book}'은(는) 존재하지 않는 책입니다.")
        return
    elif book in loans.get(user, []):
        print(f"ERROR: {user}님은 이미 '{book}'을(를) 대출 중입니다.")
        return
    elif books[book] <= 0:
        print(f"ERROR: '{book}'의 재고가 없습니다.")
        return
#대출 중인 사용자가 재고 0권의 상황을 확인해야만 대출 상태에 대한 안내를 받을 수 있는 점을 수정함.
    books[book] -= 1
    loans.setdefault(user, []).append(book)
    print(f"{user}님이 '{book}'을(를) 대출했습니다.")


def return_book(books, loans, parts):
    if len(parts) != 3:
        print("ERROR: return 명령어 형식이 올바르지 않습니다. (예: return 사용자 책이름)")
        return
    _, user, book = parts
    if not no_space(user) or not no_space(book):
        print("ERROR: 사용자 이름과 책 이름에는 공백을 포함할 수 없습니다.")
        return    
    if book not in loans.get(user, []):
        print(f"ERROR: {user}님은 '{book}'을(를) 대출한 상태가 아닙니다.")
        return

    loans[user].remove(book)
    books[book] += 1
    print(f"{user}님이 '{book}'을(를) 반납했습니다.")


def status_book(books, parts):
    if len(parts) != 2:
        print("ERROR: status 명령어 형식이 올바르지 않습니다. (예: status 책이름)")
        return
    _, name = parts

    if name not in books:
        print(f"ERROR: '{name}'은(는) 존재하지 않는 책입니다.")
        return
    print(f"{name}: {books[name]}권 남음")


def user_status(loans, parts):
    if len(parts) != 2:
        print("ERROR: user 명령어 형식이 올바르지 않습니다. (예: user 사용자)")
        return
    _, user = parts

    borrowed = loans.get(user, [])
    if not borrowed:
        print("EMPTY")
        return
    print(", ".join(borrowed))


def list_books(books, parts):
    if len(parts) != 1:
        print("ERROR: list 명령어는 추가 인자를 받지 않습니다.")
        return
    if not books:
        print("EMPTY")
        return
    for name, qty in books.items():
        print(f"{name}: {qty}권")


def main():
    books = {}   # {책이름: 남은 수량}
    loans = {}   # {사용자: [대출중인 책이름, ...]}

    
    commands = {
        "add": lambda parts: add_book(books, parts),
        "borrow": lambda parts: borrow_book(books, loans, parts),
        "return": lambda parts: return_book(books, loans, parts),
        "status": lambda parts: status_book(books, parts),
        "user": lambda parts: user_status(loans, parts),
        "list": lambda parts: list_books(books, parts),
    }
#사용자가 입력한 명령어와 실제 기능을 구현한 함수를 딕셔너리로 연결지음.
    while True:
        line = input()
        parts = line.split()

        if not parts:
            print("ERROR: 명령어를 입력해주세요.")
            continue

        command = parts[0]

        if command == "Exit":
            break

        if command in commands:
            commands[command](parts)
        else:
            print(f"ERROR: 알 수 없는 명령어입니다. ({command})")


if __name__ == "__main__":
    main()