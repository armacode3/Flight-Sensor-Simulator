import pandas as pd
import matplotlib.pyplot as plt
import sys

if len(sys.argv) < 2:
     print("Error: Please provide a filename.")
     print("Usage: python plot_data.py your_data_file.csv")
     exit()

input_file = sys.argv[1]

try:
    df = pd.read_csv(input_file)
except FileNotFoundError:
    print(f"Error: {input_file} not found.")
    exit()

# Algitude Figures
fig, ax = plt.subplots(figsize=(12, 8))

ax.plot(df['Time'], df['TrueAlt'], label='True Altitude', color='blue', linewidth=2)

ax.plot(df['Time'], df['EstAlt'], label='Estimated Altitude', color='red', linestyle='--', linewidth=2)

ax.set_title('Rocket Altitude vs. Time', fontsize=16)
ax.set_xlabel('Time (seconds)', fontsize=12)
ax.set_ylabel('Altitude (meters)', fontsize=12)
ax.legend()
ax.grid(True)

# Velocity Figures
fig_vel, ax_vel = plt.subplots(figsize=(12,8))

ax_vel.plot(df['Time'], df['TrueVel'], label='True Velocity', color='green')

ax_vel.plot(df['Time'], df['EstVel'], label='Estimated Velocity', color='purple', linestyle='--')

ax_vel.set_title('Rocket Velocity vs. Time')
ax_vel.set_xlabel('Time (s)')
ax_vel.set_ylabel('Velocity (m/s)')
ax_vel.legend()
ax_vel.grid(True)

fig.savefig('altitude_plot.png')

fig_vel.savefig('velocity_plot.png')

print("Plots saved to altitude_plot.png and velocity_plot.png")