# Video Script — Print a Stack Backwards

**Total time: ~2.5–3 minutes.** Don't rush. Pausing to breathe reads as confidence, not brain fog.

Each section says what to have on screen. Bold lines are your anchor sentences — if you fog out, just find the next bold line and keep going.

---

## 1. Intro (screen: whole file, scrolled to top)

**"Hi, I'm Jacob Cisneros, and for this assignment I chose 'print a stack backwards' using a linked list."**

"The tricky part of this one is that a stack only lets you see the top item — so to print it backwards, meaning bottom-first, I used recursion. I'll walk through the code and then run it."

---

## 2. The Node class (screen: lines 4–10)

**"First is my Node class. Each node holds one character and a pointer called `next`."**

"`next` points to the node underneath it in the stack — the thing that was pushed right before this one. The constructor just starts every node empty, with `next` set to nullptr."

---

## 3. The Stack class (screen: lines 12–15)

**"The Stack class only really needs to remember one thing: a pointer to the top node."**

"Everything else in the stack is reachable by following the `next` pointers down from the top."

---

## 4. push and pop (screen: lines 18–40)

**"Push makes a new node, points it at the current top, and then makes it the new top."**

"So the newest item is always at the front of the linked list."

**"Pop does the reverse — it saves the top's character, moves the top pointer down one, deletes the old node so there's no memory leak, and returns the character."**

"And `isEmpty` just checks whether the top pointer is nullptr — if it is, there's nothing in the stack."

---

## 5. printBackwards — the main event (screen: lines 42–52)

Slow down here. This is the part that earns the points.

**"printBackwards is recursive, and the trick is *where* the cout is — it comes AFTER the recursive call."**

Walk it step by step:

"First, the base case: if the stack is empty, just return. That's what stops the recursion."

"Otherwise, I pop the top item and hold onto it, then call printBackwards again on the rest of the stack. I don't print yet."

**"Because the printing happens after the recursive call, nothing actually prints until we hit the bottom of the stack — then everything prints on the way back up, so the bottom item comes out first."**

"And the last line pushes the held item back on, so when the recursion unwinds, the stack ends up exactly how it started. Printing it doesn't destroy it."

*(Optional, if you're feeling good — quick concrete example:)*
"So with D on top: it pops D, then C, then B, then A, hits empty — then prints A, B, C, D as each call finishes and pushes each one back."

---

## 6. main + run it (screen: main, then the terminal)

**"In main I push A, B, C, D — so D ends up on top."**

"Then I call printBackwards, and after that I pop everything off normally to prove the stack survived the backwards print."

*(Compile and run — you can do this on camera or have output ready:)*

```
g++ Cisneros_Jacob_StackBackwards_Attempt2.cpp -o stack && ./stack
```

**"Backwards prints A B C D — bottom first. Then the normal pops print D C B A — top first, which proves everything got pushed back in the right order."**

---

## 7. Outro

**"So that's my stack, built on a linked list, printed backwards with recursion, without losing any data. Thanks for watching."**

---

## Emergency lines (if you totally blank)

- "Let me just re-run it and show the output again." *(buys you 10 seconds)*
- "The key idea here is: pop everything, print on the way back up, push everything back."
- It's a recorded video — you can pause, breathe, and re-record any section. Nobody sees the takes you throw away.
