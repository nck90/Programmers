
class QueueNode {
  constructor(value) {
    this.value = value;
    this.next = null;
  }
}

class Queue {
  constructor() {
    this.head = null;
    this.tail = null;
  }

  push(value) {
    const newNode = new QueueNode(value);
    if (!this.head) {
      this.head = newNode;
      this.tail = newNode;
      return;
    }
    this.tail.next = newNode;
    this.tail = this.tail.next;
  }

  pop() {
    const { value } = this.head;
    this.head = this.head.next;
    if (!this.head) {
      this.tail = null;
    }
    return value;
  }

  empty() {
    return !this.head;
  }
}

const dx = [0, 0, 1, -1];
const dy = [1, -1, 0, 0];

function isValidPos(x, y, n, m) {
  return x >= 0 && x < n && y >= 0 && y < m;
}

function countValidRoots(grid, n, m, cur, dest, visited) {
  if (!visited) {
    visited = new Array(n).fill().map(() => new Array(m).fill(false));
    visited[cur[0]][cur[1]] = true;
  }

  const queue = new Queue();
  queue.push(cur);
  let ret = 0;
  while (!queue.empty()) {
    const pos = queue.pop();
    if (ret > 1) return ret;
    for (let k = 0; k < 4; k++) {
      const mx = pos[0] + dx[k];
      const my = pos[1] + dy[k];
      if (
        isValidPos(mx, my, n, m) &&
        !visited[mx][my] &&
        grid[mx][my] !== '#'
      ) {
        if (mx === dest[0] && my === dest[1]) {
          ret++;
        } else {
          visited[mx][my] = true;
          queue.push([mx, my]);
        }
      }
    }
  }
  return ret;
}

function findStartEnd(n, m, grid) {
  let start = null;
  let end = null;

  for (let i = 0; i < n; i++) {
    for (let j = 0; j < m; j++) {
      if (grid[i][j] === 'o') {
        if (!start) {
          start = [i, j];
        } else {
          end = [i, j];
        }
      }
    }
  }
  return { start, end };
}

function getDist(n, m, grid, start, end) {
  const visited = new Array(n).fill().map(() => new Array(m).fill(false));
  const queue = new Queue();
  queue.push([start, 0]);
  visited[start[0]][start[1]] = true;
  while (!queue.empty()) {
    const [pos, dist] = queue.pop();
    if (pos[0] === end[0] && pos[1] === end[1]) {
      return dist - 1;
    }
    for (let k = 0; k < 4; k++) {
      const mx = pos[0] + dx[k];
      const my = pos[1] + dy[k];
      if (
        isValidPos(mx, my, n, m) &&
        !visited[mx][my] &&
        grid[mx][my] !== '#'
      ) {
        visited[mx][my] = true;
        queue.push([[mx, my], dist + 1]);
      }
    }
  }

  return -1;
}

function getSnowCounts(n, m, mergedMap) {
  const ret = {
    aTotal: 0,
    bTotal: 0,
    commonTotal: 0,
  };
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < m; j++) {
      if (mergedMap[i][j] === 1 << 0) ret.aTotal++;
      if (mergedMap[i][j] === 1 << 1) ret.bTotal++;
      if (mergedMap[i][j] === ((1 << 0) | (1 << 1))) ret.commonTotal++;
    }
  }

  return ret;
}

function fillMergedMap(n, m, grid, start, mergedMap, flag) {
  const visited = new Array(n).fill().map(() => new Array(m).fill(false));
  const queue = new Queue();
  queue.push(start);
  visited[start[0]][start[1]] = true;
  mergedMap[start[0]][start[1]] |= flag;
  while (!queue.empty()) {
    const pos = queue.pop();
    for (let k = 0; k < 4; k++) {
      const mx = pos[0] + dx[k];
      const my = pos[1] + dy[k];
      if (
        isValidPos(mx, my, n, m) &&
        !visited[mx][my] &&
        grid[mx][my] !== '#'
      ) {
        visited[mx][my] = true;
        mergedMap[mx][my] |= flag;
        if (grid[mx][my] !== 'o') {
          queue.push([mx, my]);
        }
      }
    }
  }
}

function checkRotatable(n, m, mergedMap, flag, start) {
  const visited = new Array(n).fill().map(() => new Array(m).fill(false));
  const queue = new Queue();
  queue.push([start, 1]);
  visited[start[0]][start[1]] = true;
  let latestCount = 1;
  while (!queue.empty()) {
    const [pos, count] = queue.pop();
    latestCount = count;
    let valids = 0;
    for (let k = 0; k < 4; k++) {
      const mx = pos[0] + dx[k];
      const my = pos[1] + dy[k];
      if (!isValidPos(mx, my, n, m)) continue;
      if (mergedMap[mx][my] !== flag) continue;
      if (visited[mx][my]) continue;
      valids++;
      visited[mx][my] = true;
      queue.push([[mx, my], count + 1]);
    }
    if (valids >= 2) return [true, count];
  }

  return [false, latestCount - 1];
}

function calculator(aLeft, aRight, bLeft, bRight, common, total) {
  let ret = 0;
  for (let b = bLeft; b <= bRight; b++) {
    const aMin = Math.max(aLeft, common - b, b);
    const aMax = Math.min(aRight, total - b);

    if (aMin <= aMax) {
      ret += aMax - aMin + 1;
    }
  }
  return ret;
}

function calculate(
  isARotateble,
  aLeast,
  aTotal,
  isBRotatable,
  bLeast,
  bTotal,
  commonLeast,
  commonTotal,
  validRootCounts,
) {
  const totalSnowCounts = commonTotal + aTotal + bTotal;

  if (!isARotateble) {
    const [min, max] = aTotal < bTotal ? [aTotal, bTotal] : [bTotal, aTotal];
    return calculator(
      1,
      max + commonTotal - 1,
      1,
      min + commonTotal - 1,
      commonLeast,
      totalSnowCounts,
    );
  }
  if (!isBRotatable) {
    const case1 = calculator(
      1,
      aLeast,
      1,
      commonTotal + bTotal - 1,
      commonLeast,
      totalSnowCounts,
    );

    const case2 = calculator(
      aLeast + 1,
      totalSnowCounts - 1,
      1,
      totalSnowCounts - 1,
      commonLeast,
      totalSnowCounts,
    );

    return case1 + case2;
  }
  let [minLeast, minTotal, maxLeast, maxTotal] =
    aLeast > bLeast
      ? [bLeast, bTotal, aLeast, aTotal]
      : [aLeast, aTotal, bLeast, bTotal];
  const case1 = calculator(
    1,
    minLeast,
    1,
    commonTotal + maxTotal - 1,
    commonLeast,
    totalSnowCounts,
  );

  const case2 = calculator(
    minLeast + 1,
    totalSnowCounts - 1,
    1,
    totalSnowCounts - 1,
    commonLeast,
    totalSnowCounts,
  );

  return case1 + case2;
}

function solution(grid) {
  grid = grid.map(el => el.split(''));
  const n = grid.length;
  const m = grid[0].length;
  const { start, end } = findStartEnd(n, m, grid);
  const mergedMap = new Array(n).fill().map(() => new Array(m).fill(0));
  fillMergedMap(n, m, grid, start, mergedMap, 1 << 0);
  fillMergedMap(n, m, grid, end, mergedMap, 1 << 1);
  const [aCommonRotatable, aCounts] = checkRotatable(
    n,
    m,
    mergedMap,
    (1 << 0) | (1 << 1),
    start,
  );
  const [bCommonRotatable, bCounts] = checkRotatable(
    n,
    m,
    mergedMap,
    (1 << 0) | (1 << 1),
    end,
  );

  const dist = getDist(n, m, grid, start, end);
  const validRootCounts = countValidRoots(grid, n, m, start, end);
  let [isARotateble, aLeast] = checkRotatable(n, m, mergedMap, 1 << 0, start);
  let [isBRotatable, bLeast] = checkRotatable(n, m, mergedMap, 1 << 1, end);

  if (aCommonRotatable) {
      if (isARotateble) {
        aLeast = Math.min(aLeast, aCounts);
      } else {
        aLeast = aCounts;
        isARotateble = true;
      }
  }
  if (bCommonRotatable) {
      if (isBRotatable) {
        bLeast = Math.min(bLeast, bCounts);
      } else {
        bLeast = bCounts;
        isBRotatable = true;
      }
  }
  let { commonTotal, aTotal, bTotal } = getSnowCounts(n, m, mergedMap);
  if (!isARotateble) {
    [isARotateble, aLeast, aTotal, isBRotatable, bLeast, bTotal] = [
      isBRotatable,
      bLeast,
      bTotal,
      isARotateble,
      aLeast,
      aTotal,
    ];
  }

  return calculate(
    isARotateble,
    aLeast,
    aTotal,
    isBRotatable,
    bLeast,
    bTotal,
    dist + 2,
    commonTotal,
    validRootCounts,
  );
}