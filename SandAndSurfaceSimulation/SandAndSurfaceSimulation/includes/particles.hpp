#pragma once
struct Particle {
	/// <summary>
	/// Liquid will move to the direct left and direct right if free, or straight down.
	/// </summary>
	bool isLiquid;
	/// <summary>
	/// Sand will move to diagonally left and right, or straight down.
	/// </summary>
	bool isSand;
	/// <summary>
	/// Solid objects will not move.
	/// </summary>
	bool isSolid;
	/// <summary>
	/// Flammable objects can be ignited, emitting smoke and decaying over time.
	/// </summary>
	bool isFlammable;

	/// <summary>
	/// Every time this particle is checked, its survival chance is rolled.
	/// If it rolls under the survival chance, it stays. If it doesn't, it is removed.
	/// </summary>
	float survivalChance;

	/// <summary>
	/// If material is liquid or sand, it will move down like it's under empty space.
	/// </summary>
	int density;

	/// <summary>
	/// Current spot on the grid for this particle.
	/// </summary>
	int currentSpot[2];

	/// <summary>
	/// When this particle can make a valid move, mark this spot as filled.
	/// </summary>
	int nextSpot[2];
};