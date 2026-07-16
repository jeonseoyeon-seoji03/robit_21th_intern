def add_book(books, parts):
    """책 등록. 이미 있으면 수량을 더한다."""
    if len(parts) != 3:
        print("ERROR: add 명령어 형식이 올바르지 않습니다. (예: add 책이름 수량)")
        return
    _, name, qty_str = parts
    if not qty_str.isdigit():
        print("ERROR: 수량은 0 이상의 정수여야 합니다.")
        return
    qty = int(qty_str)
    books[name] = books.get(name, 0) + qty
    print(f"{name} {qty}권 등록 완료 (현재 재고: {books[name]}권)")


def borrow_book(books, loans, parts):
    """책이 존재하고, 재고가 있고, 같은 사용자가 중복 대출 중이 아닐 때만 대출."""
    if len(parts) != 3:
        print("ERROR: borrow 명령어 형식이 올바르지 않습니다. (예: borrow 사용자 책이름)")
        return
    _, user, book = parts

    if book not in books:
        print(f"ERROR: '{book}'은(는) 존재하지 않는 책입니다.")
        return
    if books[book] <= 0:
        print(f"ERROR: '{book}'의 재고가 없습니다.")
        return
    if book in loans.get(user, []):
        print(f"ERROR: {user}님은 이미 '{book}'을(를) 대출 중입니다.")
        return

    books[book] -= 1
    loans.setdefault(user, []).append(book)
    print(f"{user}님이 '{book}'을(를) 대출했습니다.")


def return_book(books, loans, parts):
    """실제로 대출 중인 책만 반납 가능."""
    if len(parts) != 3:
        print("ERROR: return 명령어 형식이 올바르지 않습니다. (예: return 사용자 책이름)")
        return
    _, user, book = parts

    if book not in loans.get(user, []):
        print(f"ERROR: {user}님은 '{book}'을(를) 대출 중이지 않습니다.")
        return

    loans[user].remove(book)
    books[book] += 1
    print(f"{user}님이 '{book}'을(를) 반납했습니다.")


def status_book(books, parts):
    """책의 남은 수량 출력. 없으면 ERROR."""
    if len(parts) != 2:
        print("ERROR: status 명령어 형식이 올바르지 않습니다. (예: status 책이름)")
        return
    _, name = parts

    if name not in books:
        print(f"ERROR: '{name}'은(는) 존재하지 않는 책입니다.")
        return
    print(f"{name}: {books[name]}권 남음")


def user_status(loans, parts):
    """사용자의 대출 목록 출력. 없으면 EMPTY."""
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
    """전체 책 목록을 등록 순서대로 출력."""
    if len(parts) != 1:
        print("ERROR: list 명령어는 추가 인자를 받지 않습니다.")
        return
    if not books:
        print("EMPTY")
        return
    for name, qty in books.items():   # 딕셔너리는 등록 순서를 유지하므로 그대로 순회
        print(f"{name}: {qty}권")


def main():
    books = {}   # {책이름: 남은 수량}
    loans = {}   # {사용자: [대출중인 책이름, ...]}

    # 명령어 문자열 -> 처리 함수 매핑 (if-elif 나열 대신 사용)
    commands = {
        "add": lambda parts: add_book(books, parts),
        "borrow": lambda parts: borrow_book(books, loans, parts),
        "return": lambda parts: return_book(books, loans, parts),
        "status": lambda parts: status_book(books, parts),
        "user": lambda parts: user_status(loans, parts),
        "list": lambda parts: list_books(books, parts),
    }

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