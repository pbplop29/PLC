import csv
import matplotlib.pyplot as plt

cycles, start_button, pump_running = [], [], []

with open("plc/build/run_log.csv") as f:
    for row in csv.DictReader(f):
        cycles.append(int(row["cycle"]))
        start_button.append(int(row["start_button"]))
        pump_running.append(int(row["pump_running"]))

# each signal gets its own lane, like a logic analyzer: 0/1 + a vertical offset
LANE_HEIGHT = 1.5
signals = [
    ("start_button", start_button, 1),
    ("pump_running", pump_running, 0),
]

fig, ax = plt.subplots(figsize=(8, 3))

for name, values, lane in signals:
    y = [v + lane * LANE_HEIGHT for v in values]
    ax.step(cycles, y, where="post", linewidth=2)
    ax.text(cycles[0] - 0.4, lane * LANE_HEIGHT + 0.5, name, va="center", ha="right")

ax.set_xlabel("scan cycle")
ax.set_xticks(cycles)
ax.set_yticks([])
ax.set_title("PLC signals over 10 scan cycles")
ax.set_xlim(cycles[0] - 1, cycles[-1] + 0.5)
ax.grid(axis="x", linestyle=":", alpha=0.5)

fig.tight_layout()
fig.savefig("plc/build/waveform.png", dpi=150)
print("saved plc/build/waveform.png")
